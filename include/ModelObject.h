//
// Created by Андрей on 19.10.17.
//

#ifndef YET_ANOTHER_ENGINE_MODELOBJECT_HPP
#define YET_ANOTHER_ENGINE_MODELOBJECT_HPP


#include "AbstractObject.h"
#include "Model.h"

class ModelObject: public AbstractObject
{
public:
    ModelObject(ShaderProgram&, Model&);
    virtual ~ModelObject();
    void draw(glm::mat4) const override;

protected:
    Model& model;
};


#endif //YET_ANOTHER_ENGINE_MODELOBJECT_HPP
