//
// Created by Андрей on 17.10.17.
//

#include <glm/gtc/matrix_transform.hpp>
#include "Model.h"

Model::Model(ShaderProgram& program):
    program(program), _vao_guid(0), _vbo_guid(0), _ebo_guid(0) { }

void Model::load()
{
    if (this->_isLoaded) return;

    glGenVertexArrays(1, &this->_vao_guid);
    glGenBuffers(1, &this->_vbo_guid);
    glGenBuffers(1, &this->_ebo_guid);

    glBindVertexArray(this->_vao_guid);
    glBindBuffer(GL_ARRAY_BUFFER, this->_vbo_guid);
    // TODO: передавть всегда vertex избыточно, так как все зависит от шейда и например цвет ему передавать не нужно
    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(vertex), &_vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ebo_guid);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indexes.size() * sizeof(unsigned int), &_indexes[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)sizeof(vertex::coordinate));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    this->_isLoaded = true;
}

void Model::unload()
{
    this->_isLoaded = false;
    glDeleteBuffers(1, &this->_ebo_guid);
    glDeleteBuffers(1, &this->_vbo_guid);
    glDeleteVertexArrays(1, &this->_vao_guid);
}

void Model::drawModel(glm::mat4 proj_view, glm::mat4 model) const
{
    this->program.use();
    this->program.set_uniform("proj_view", proj_view);
    this->program.set_uniform("model", model);
    glBindVertexArray(this->_vao_guid);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(_indexes.size()), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}
