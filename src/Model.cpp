//
// Created by Андрей on 17.10.17.
//

#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include "Model.h"

Model::Model(const char* path):
        _path_to_source(path), _vao_guid(0), _vbo_guid(0), _ebo_guid(0) { }

void Model::load()
{
    if (this->_isLoaded) return;

    Assimp::Importer importer; // TODO maybe can be static
    // если использовать unique_ptr, то свалится с ошибкой. Надо разобраться
    // auto scene = std::unique_ptr<const aiScene>(importer.ReadFile(_path_to_source, aiProcess_Triangulate | aiProcess_FlipUVs));
    auto scene = importer.ReadFile(_path_to_source, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene)
    {
        throw 1;
    }

    glm::mat4 transform = glm::scale(glm::mat4(1), glm::vec3(.5f));
    for (unsigned int mesh_index = 0; mesh_index < 1; mesh_index++)
    {
        aiMesh *mesh = scene->mMeshes[mesh_index];
        for (unsigned int vert_index = 0; vert_index < mesh->mNumVertices; vert_index++)
        {
            aiVector3D vert = mesh->mVertices[vert_index];
            glm::vec3 vertex = transform * glm::vec4(vert.x, vert.y, vert.z, 1.f);
            _vertices.push_back(vertex);
        }
        for (unsigned int face_index = 0; face_index < mesh->mNumFaces; face_index++)
        {
            aiFace face = mesh->mFaces[face_index];
            _indexes.insert(_indexes.end(), face.mIndices, face.mIndices + face.mNumIndices);
        }
    }

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

void Model::drawModel() const
{
    glBindVertexArray(this->_vao_guid);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(_indexes.size()), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}
