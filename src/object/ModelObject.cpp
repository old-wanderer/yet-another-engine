//
// Created by Андрей on 19.10.17.
//

#include "ModelObject.h"

ModelObject::ModelObject(ShaderProgram& program,Model& model):
        AbstractObject(program), model(model) { }

ModelObject::~ModelObject()
{

}

void ModelObject::draw() const
{
    this->program.use();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    model.drawModel();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
