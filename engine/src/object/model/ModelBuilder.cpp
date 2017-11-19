//
// Created by Андрей on 29.10.17.
//

#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>

#include "engine/ModelBuilder.h"

ModelBuilder &ModelBuilder::setProgram(ShaderProgram &program)
{
    ModelBuilder::program = &program;
    return *this;
}

Model *ModelBuilder::build()
{
    auto * model = new Model(*program);

    std::copy(vertices.begin(), vertices.end(), std::back_inserter(model->_vertices));
    std::copy(indices.begin(), indices.end(), std::back_inserter(model->_indexes));

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


//    if (scene->mNumMaterials) {
//        for (uint32_t material_index = 0; material_index < scene->mNumMaterials; material_index++)
//        {
//            std::cout << "----------------------" << std::endl;
//            aiMaterial *material = scene->mMaterials[material_index];
//            aiString texture_path;
//            if(material->GetTexture(aiTextureType_DIFFUSE, 0, &texture_path) == AI_SUCCESS)
//            {
//                std::cout << "texture path: " << texture_path.C_Str() << std::endl;
//            }
//        }
//    }

    // NOTE: количество вершин и индексов равно, чего быть не должно с ball.вфу
    for (unsigned int mesh_index = 0; mesh_index < scene->mNumMeshes; mesh_index++)
    {
        std::vector<vertex> mesh_vertices;
        std::vector<uint32_t> mesh_indices;
        aiMesh *mesh = scene->mMeshes[mesh_index];
        for (unsigned int vert_index = 0; vert_index < mesh->mNumVertices; vert_index++)
        {
            aiVector3D vert = mesh->mVertices[vert_index];
            vertex vertex = { glm::vec3(vert.x, vert.y, vert.z) };
            if (mesh->HasVertexColors(0)) {
                aiColor4D* color = mesh->mColors[0];
                vertex.color = glm::vec3(color->r, color->g, color->b);
            }
//            push_back_vertex(vertex);
            mesh_vertices.push_back(vertex);
        }
        for (unsigned int face_index = 0; face_index < mesh->mNumFaces; face_index++)
        {
            aiFace face = mesh->mFaces[face_index];
//            push_back_all_indices(face.mIndices, face.mIndices + face.mNumIndices);
            mesh_indices.insert(mesh_indices.end(), face.mIndices, face.mIndices + face.mNumIndices);
        }
        meshes.emplace_back(std::forward<std::vector<vertex>>(mesh_vertices),
                            std::forward<std::vector<uint32_t>>(mesh_indices));
    }

    return *this;
}

ModelBuilder &ModelBuilder::set_color_vertex(unsigned int index, glm::vec3 color)
{
    vertices[index].color = color;
    return *this;
}
