//
// Created by Андрей on 17.10.17.
//

#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include "Model.h"

Model::Model(ShaderProgram& program, std::vector<glm::vec3> &&vertices, std::vector<unsigned int> &&indexes):
    program(program), _vertices(vertices), _indexes(indexes), _vao_guid(0), _vbo_guid(0), _ebo_guid(0) { }

Model *Model::from_file(ShaderProgram& program, const std::string &path)
{
    std::vector<glm::vec3> vertices;
    std::vector<unsigned int> indexes;

    Assimp::Importer importer; // TODO maybe can be static
    // NOTE: если использовать unique_ptr, то свалится с ошибкой. Надо разобраться
    // auto scene = std::unique_ptr<const aiScene>(importer.ReadFile(_path_to_source, aiProcess_Triangulate | aiProcess_FlipUVs));
    auto scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene)
    {
        throw 1;
    }

    // NOTE: количество вершин и индексов равно, чего быть не должно с ball.вфу
    for (unsigned int mesh_index = 0; mesh_index < 1; mesh_index++)
    {
        aiMesh *mesh = scene->mMeshes[mesh_index];
        for (unsigned int vert_index = 0; vert_index < mesh->mNumVertices; vert_index++)
        {
            aiVector3D vert = mesh->mVertices[vert_index];
            vertices.emplace_back(vert.x, vert.y, vert.z);
        }
        for (unsigned int face_index = 0; face_index < mesh->mNumFaces; face_index++)
        {
            aiFace face = mesh->mFaces[face_index];
            indexes.insert(indexes.end(), face.mIndices, face.mIndices + face.mNumIndices);
        }
    }

    return new Model(program,
                     std::forward<std::vector<glm::vec3>>(vertices),
                     std::forward<std::vector<unsigned int>>(indexes));
}

// NOTE: теоритически эти параметры не нужны,
// так с помощью матрицы объекты можно сделать что угодно
Model *Model::from_rectangle(ShaderProgram& program,GLfloat, GLfloat, glm::vec3)
{
    std::vector<glm::vec3> vertices;
    std::vector<unsigned int> indexes = { 0, 1, 2, 1, 2, 3};

    vertices.emplace_back(-0.5f, 0.0f, -0.5f);
    vertices.emplace_back(-0.5f, 0.0f,  0.5f);
    vertices.emplace_back( 0.5f, 0.0f, -0.5f);
    vertices.emplace_back( 0.5f, 0.0f,  0.5f);

    return new Model(program,
                     std::forward<std::vector<glm::vec3>>(vertices),
                     std::forward<std::vector<unsigned int>>(indexes));
}

void Model::load()
{
    if (this->_isLoaded) return;

    glGenVertexArrays(1, &this->_vao_guid);
    glGenBuffers(1, &this->_vbo_guid);
    glGenBuffers(1, &this->_ebo_guid);

    glBindVertexArray(this->_vao_guid);
    glBindBuffer(GL_ARRAY_BUFFER, this->_vbo_guid);
    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(glm::vec3), &_vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ebo_guid);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indexes.size() * sizeof(unsigned int), &_indexes[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    this->_isLoaded = true;
}

void Model::unload()
{
    this->_isLoaded = false;
    glDeleteBuffers(1, &this->_ebo_guid);
    glDeleteBuffers(1, &this->_vbo_guid);
    glDeleteVertexArrays(1, &this->_vao_guid);
}

void Model::drawModel(glm::mat4 proj_view, glm::mat4 model) const
{
    this->program.use();
    this->program.set_uniform("proj_view", proj_view);
    this->program.set_uniform("model", model);
    glBindVertexArray(this->_vao_guid);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(_indexes.size()), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}
