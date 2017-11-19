//
// Created by Андрей on 17.10.17.
//

#include <glm/gtc/matrix_transform.hpp>
#include "engine/Model.h"


Model::Model(ShaderProgram& program): program(program), _vao_guid(0), _vbo_guid(0), _ebo_guid(0) { }

void Model::load()
{
    if (this->_isLoaded) return;

    for (auto& mesh: meshes)
    {
        mesh.load();
    }

    this->_isLoaded = true;
}

void Model::unload()
{
    this->_isLoaded = false;
    for (auto& mesh: meshes)
    {
        mesh.unload();
    }
}

void Model::drawModel(glm::mat4 proj_view, glm::mat4 model) const
{
    this->program.use();
    this->program.set_uniform("proj_view", proj_view);
    this->program.set_uniform("model", model);
    for (auto& mesh: meshes)
    {
        mesh.draw();
    }
}
