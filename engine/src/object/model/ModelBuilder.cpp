//
// Created by Андрей on 29.10.17.
//

#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <iostream>

#include "engine/ModelBuilder.h"

ModelBuilder &ModelBuilder::setProgram(ShaderProgram &program)
{
    ModelBuilder::program = &program;
    return *this;
}

Model *ModelBuilder::build()
{
    auto * model = new Model(*program);
    std::copy(meshes.begin(), meshes.end(), std::back_inserter(model->meshes));

    return model;
}

ModelBuilder &ModelBuilder::push_back_all_indices(unsigned int *begin, unsigned int * end)
{
    ModelBuilder::indices.insert(ModelBuilder::indices.end(), begin, end);
    return *this;
}

ModelBuilder &ModelBuilder::push_back_all_indices(std::initializer_list<unsigned int> list)
{
    ModelBuilder::indices.insert(ModelBuilder::indices.end(), list);
    return *this;
}

ModelBuilder &ModelBuilder::push_back_vertex(glm::vec3 coord, glm::vec3 color)
{
    vertices.push_back({coord, color});
    return *this;
}

ModelBuilder &ModelBuilder::push_back_vertex(vertex vertex)
{
    vertices.push_back(vertex);
    return *this;
}

ModelBuilder &ModelBuilder::push_back_indices(unsigned int)
{
    return *this;
}

ModelBuilder &ModelBuilder::import_from_file(const std::string &path)
{
    vertices.clear();
    indices.clear();

    Assimp::Importer importer; // TODO maybe can be static
    // NOTE: если использовать unique_ptr, то свалится с ошибкой. Надо разобраться
    // auto scene = std::unique_ptr<const aiScene>(importer.ReadFile(_path_to_source, aiProcess_Triangulate | aiProcess_FlipUVs));
    auto scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene)
    {
        throw 1;
    }

    std::vector<std::shared_ptr<Texture>> textures;
    if (scene->mNumMaterials) {
        for (uint32_t material_index = 0; material_index < scene->mNumMaterials; material_index++)
        {
            aiMaterial *material = scene->mMaterials[material_index];
            aiString texture_path;
            if(material->GetTexture(aiTextureType_DIFFUSE, 0, &texture_path) == AI_SUCCESS)
            {
                std::string _path;
                _path.append("./resource/model/").append(texture_path.C_Str());
                textures.emplace_back(new Texture(std::forward<std::string>(_path)));
            }
        }
    }

    // NOTE: количество вершин и индексов равно, чего быть не должно с ball.вфу
    for (unsigned int mesh_index = 0; mesh_index < scene->mNumMeshes; mesh_index++)
    {
        aiMesh *aimesh = scene->mMeshes[mesh_index];
        uint32_t inputs = ShaderInputData::VERTEX;
        if (aimesh->HasVertexColors(0))
        {
            inputs |= ShaderInputData::VERTEX_COLOR;
        }
        if (aimesh->HasTextureCoords(0))
        {
            inputs |= ShaderInputData::VERTEX_TEXTURE_COORD;
        }

        Mesh mesh(inputs);
        if (aimesh->mMaterialIndex)
        {
            mesh._texture = textures[aimesh->mMaterialIndex - 1];
            mesh._texture->load();
        }
        for (unsigned int vert_index = 0; vert_index < aimesh->mNumVertices; vert_index++)
        {
            aiVector3D vert = aimesh->mVertices[vert_index];
            vertex vertex = { glm::vec3(vert.x, vert.y, vert.z) };
            if (inputs & ShaderInputData::VERTEX_COLOR) {
                aiColor4D color = aimesh->mColors[0][vert_index];
                vertex.color = glm::vec3(color.r, color.g, color.b);
            }
            if (inputs & ShaderInputData::VERTEX_TEXTURE_COORD)
            {
                aiVector3D texture_coord = aimesh->mTextureCoords[0][vert_index];
                vertex.texture_coordinate = glm::vec2(texture_coord.x, 1.f - texture_coord.y);
            }
            mesh._vertices.push_back(vertex);
        }
        for (unsigned int face_index = 0; face_index < aimesh->mNumFaces; face_index++)
        {
            aiFace face = aimesh->mFaces[face_index];
            mesh._indices.insert(mesh._indices.end(), face.mIndices, face.mIndices + face.mNumIndices);
        }
        meshes.emplace_back(std::forward<Mesh>(mesh));
    }

    return *this;
}

ModelBuilder &ModelBuilder::set_color_vertex(unsigned int index, glm::vec3 color)
{
    vertices[index].color = color;
    return *this;
}
