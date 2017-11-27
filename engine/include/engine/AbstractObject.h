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
    friend class ObjectBuilder;
public:
    explicit AbstractObject(Model&, glm::mat4&& = glm::mat4(1), bool = true);
    virtual ~AbstractObject() = default;

    void draw(glm::mat4) const;
    void move(glm::vec3);

protected:
    Model& object_model;
    glm::mat4 mat_model;

    bool polygon_mode_is_fill;
};


#endif //YET_ANOTHER_ENGINE_ABSTRACTOBJECT_H
