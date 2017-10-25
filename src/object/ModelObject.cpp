//
// Created by Андрей on 19.10.17.
//

#include "ModelObject.h"

ModelObject::ModelObject(ShaderProgram& program, Model& model, glm::mat4&& trans):
        AbstractObject(program, std::forward<glm::mat4>(trans)), model(model) { }

void ModelObject::draw(glm::mat4 proj_view) const
{
    this->program.use();
    this->program.set_uniform("proj_view", proj_view);
    this->program.set_uniform("model", global);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    model.drawModel();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
