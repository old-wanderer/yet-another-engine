//
// Created by Андрей on 20.11.2017.
//

#ifndef YET_ANOTHER_ENGINE_MESH_H
#define YET_ANOTHER_ENGINE_MESH_H


#include <vector>
#include <glm/glm.hpp>
#include "Resource.h"
#include "Texture.h"

struct vertex
{
    glm::vec3 coordinate;
    glm::vec3 color;
    glm::vec2 texture_coordinate;
};

class Mesh: public Resource
{
friend class ModelBuilder;
public:
    Mesh() = default;

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
