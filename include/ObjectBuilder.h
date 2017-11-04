//
// Created by Андрей on 04.11.17.
//

#ifndef YET_ANOTHER_ENGINE_OBJECTBUILDER_H
#define YET_ANOTHER_ENGINE_OBJECTBUILDER_H

#include <glm/glm.hpp>

#include "AbstractObject.h"

class ObjectBuilder
{
public:
    ObjectBuilder() = default;

    ObjectBuilder& translate(glm::vec3&&);
    ObjectBuilder& scale(float&&);
    ObjectBuilder& scale(glm::vec3&&);
    ObjectBuilder& rotate(float, glm::vec3&&);

    ObjectBuilder& model(Model&);

    AbstractObject* build();
protected:
    glm::vec3 _translate = glm::vec3(0);
    glm::vec3 _scale     = glm::vec3(1);
    glm::vec3 _rotate    = glm::vec3(1);
    float _angel = 0.f;
    Model* _model = nullptr;
};


#endif //YET_ANOTHER_ENGINE_OBJECTBUILDER_H
