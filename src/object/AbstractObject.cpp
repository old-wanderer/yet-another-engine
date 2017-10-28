//
// Created by Андрей on 16.10.17.
//

#include "AbstractObject.h"

AbstractObject::AbstractObject(Model& model,  glm::mat4 &&global, bool mode):
        model(model), global(global), polygon_mode_is_fill(mode) { }

void AbstractObject::draw(glm::mat4 proj_view) const
{
    if (!polygon_mode_is_fill)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    model.drawModel(proj_view, this->global);
    if (!polygon_mode_is_fill)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
