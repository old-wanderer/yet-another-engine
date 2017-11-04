//
// Created by Андрей on 04.11.17.
//

#include <glm/gtc/matrix_transform.hpp>
#include "ObjectBuilder.h"


ObjectBuilder &ObjectBuilder::translate(glm::vec3&& translate)
{
    this->_translate = translate;
    return *this;
}

ObjectBuilder &ObjectBuilder::scale(float &&scale)
{
    this->_scale = glm::vec3(scale);
    return *this;
}

ObjectBuilder &ObjectBuilder::scale(glm::vec3 &&scale)
{
    this->_scale = scale;
    return *this;
}

ObjectBuilder &ObjectBuilder::rotate(float angel, glm::vec3 &&rotate)
{
    this->_angel  = angel;
    this->_rotate = rotate;
    return *this;
}

ObjectBuilder &ObjectBuilder::model(Model &model)
{
    this->_model = &model;
    return *this;
}

AbstractObject *ObjectBuilder::build()
{
    glm::mat4 model(1);
    model = glm::translate(model, this->_translate);
    model = glm::scale(model, this->_scale);
    model = glm::rotate(model,this->_angel, this->_rotate);
    auto object = new AbstractObject(*_model, std::forward<glm::mat4>(model));

    return object;
}
