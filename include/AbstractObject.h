//
// Created by Андрей on 16.10.17.
//

#ifndef YET_ANOTHER_ENGINE_ABSTRACTOBJECT_H
#define YET_ANOTHER_ENGINE_ABSTRACTOBJECT_H

#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "ShaderProgram.h"


class AbstractObject
{
public:
    explicit AbstractObject(ShaderProgram&);
    virtual ~AbstractObject();
    virtual void draw(glm::mat4) const = 0;

protected:
    ShaderProgram& program;

    std::vector<glm::vec3> vertices;
    GLuint _vao_guid;
};


#endif //YET_ANOTHER_ENGINE_ABSTRACTOBJECT_H
