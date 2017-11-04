//
// Created by Андрей on 16.10.17.
//

#include "AbstractObject.h"

AbstractObject::AbstractObject(Model &object_model, glm::mat4&& mat_model, bool mode):
        object_model(object_model), mat_model(mat_model), polygon_mode_is_fill(mode) { }

void AbstractObject::draw(glm::mat4 proj_view) const
{
    if (!polygon_mode_is_fill)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    object_model.drawModel(proj_view, this->mat_model);
    if (!polygon_mode_is_fill)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
