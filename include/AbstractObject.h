//
// Created by Андрей on 16.10.17.
//

#ifndef YET_ANOTHER_ENGINE_ABSTRACTOBJECT_H
#define YET_ANOTHER_ENGINE_ABSTRACTOBJECT_H

#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Model.h"


class AbstractObject
{
public:
    explicit AbstractObject(Model&, glm::mat4&& = glm::mat4(1), bool = true);
    virtual ~AbstractObject() = default;
    void draw(glm::mat4) const;

protected:
    Model& model;
    glm::mat4 global;

    bool polygon_mode_is_fill;
};


#endif //YET_ANOTHER_ENGINE_ABSTRACTOBJECT_H
