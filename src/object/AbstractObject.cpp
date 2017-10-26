//
// Created by Андрей on 16.10.17.
//

#include "AbstractObject.h"

AbstractObject::AbstractObject(ShaderProgram& program, Model& model,  glm::mat4 &&global, bool mode):
        program(program), model(model), global(global), polygon_mode_is_fill(mode) { }

void AbstractObject::draw(glm::mat4 proj_view) const
{
    this->program.use();
    this->program.set_uniform("proj_view", proj_view);
    this->program.set_uniform("model", this->global);
    if (!polygon_mode_is_fill)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    model.drawModel();
    if (!polygon_mode_is_fill)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
