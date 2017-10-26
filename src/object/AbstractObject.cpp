//
// Created by Андрей on 16.10.17.
//

#include "AbstractObject.h"

AbstractObject::AbstractObject(ShaderProgram& program, Model& model):
        program(program), model(model) { }

void AbstractObject::draw(glm::mat4 proj_view) const
{
    this->program.use();
    this->program.set_uniform("proj_view", proj_view);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    model.drawModel();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}