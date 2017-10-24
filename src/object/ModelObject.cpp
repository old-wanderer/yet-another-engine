//
// Created by Андрей on 19.10.17.
//

#include "ModelObject.h"

ModelObject::ModelObject(ShaderProgram& program,Model& model):
        AbstractObject(program), model(model) { }

ModelObject::~ModelObject()
{

}

void ModelObject::draw(glm::mat4 proj_view) const
{
    this->program.use();
    this->program.set_uniform("proj_view", proj_view);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    model.drawModel();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
