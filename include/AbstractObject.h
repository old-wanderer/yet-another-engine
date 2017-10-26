//
// Created by Андрей on 16.10.17.
//

#ifndef YET_ANOTHER_ENGINE_ABSTRACTOBJECT_H
#define YET_ANOTHER_ENGINE_ABSTRACTOBJECT_H

#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Model.h"


class AbstractObject
{
public:
    explicit AbstractObject(ShaderProgram&, Model&);
    virtual ~AbstractObject() = default;
    void draw(glm::mat4) const;

protected:
    ShaderProgram& program;
    Model& model;
};


#endif //YET_ANOTHER_ENGINE_ABSTRACTOBJECT_H
