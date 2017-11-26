//
// Created by Андрей on 20.11.2017.
//

#ifndef YET_ANOTHER_ENGINE_MESH_H
#define YET_ANOTHER_ENGINE_MESH_H


#include <vector>
#include <glm/glm.hpp>
#include <array>
#include "Resource.h"
#include "Texture.h"

struct vertex
{
    glm::vec3 coordinate;
    glm::vec3 color;
    glm::vec2 texture_coordinate;

    constexpr static const std::array<size_t, 3> fields
            = { sizeof(coordinate), sizeof(color), sizeof(texture_coordinate) };
};

class Mesh: public Resource<MeshLoadContext>
{
friend class ModelBuilder;
public:
    explicit Mesh(uint32_t);

    void load() override;
    void unload() override;

    void draw() const;

protected:
    std::shared_ptr<Texture> _texture;

    std::vector<vertex> _vertices;
    std::vector<uint32_t> _indices;

    GLuint _vao_guid;
    GLuint _vbo_guid;
    GLuint _ebo_guid;
};


#endif //YET_ANOTHER_ENGINE_MESH_H
