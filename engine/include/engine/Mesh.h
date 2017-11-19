//
// Created by Андрей on 20.11.2017.
//

#ifndef YET_ANOTHER_ENGINE_MESH_H
#define YET_ANOTHER_ENGINE_MESH_H


#include <vector>
#include <glm/vec3.hpp>
#include "Resource.h"

struct vertex
{
    glm::vec3 coordinate;
    glm::vec3 color;
};

class Mesh: public Resource
{
friend class ModelBuilder;
public:

    Mesh(std::vector<vertex> &&, std::vector<uint32_t> &&);

    void load() override;
    void unload() override;

    void draw() const;

protected:

    std::vector<vertex> _vertices;
    std::vector<uint32_t> _indices;

    GLuint _vao_guid;
    GLuint _vbo_guid;
    GLuint _ebo_guid;
};


#endif //YET_ANOTHER_ENGINE_MESH_H
