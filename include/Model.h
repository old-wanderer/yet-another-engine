//
// Created by Андрей on 17.10.17.
//

#ifndef YET_ANOTHER_ENGINE_MODEL_H
#define YET_ANOTHER_ENGINE_MODEL_H

#include <string>
#include <glm/glm.hpp>
#include <vector>
#include "Resource.h"
#include "ShaderProgram.h"

struct vertex
{
    glm::vec3 coordinate;
    glm::vec3 color;
};

class Model: public Resource
{
    friend class ModelBuilder;
public:
    void load() override;
    void unload() override;

    void drawModel(glm::mat4, glm::mat4) const;
protected:
    explicit Model(ShaderProgram&);

    ShaderProgram& program;

    std::vector<vertex>       _vertices;
    std::vector<unsigned int> _indexes;

    GLuint _vao_guid;
    GLuint _vbo_guid;
    GLuint _ebo_guid;
};


#endif //YET_ANOTHER_ENGINE_MODEL_H
