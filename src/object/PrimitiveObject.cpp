//
// Created by Андрей on 16.10.17.
//

#include <iostream>
#include "PrimitiveObject.h"

PrimitiveObject::PrimitiveObject(ShaderProgram& program, glm::mat4&& model):
        AbstractObject(program, std::forward<glm::mat4>(model))
{
    vertices.emplace_back(-0.5f, -0.5f, 0.0f);
    vertices.emplace_back( 1.0f,  0.0f, 0.0f);

    vertices.emplace_back( 0.5f, -0.5f, 0.0f);
    vertices.emplace_back( 0.0f,  1.0f, 0.0f);

    vertices.emplace_back( 0.0f,  0.5f, 0.0f);
    vertices.emplace_back( 0.0f,  0.0f, 1.0f);

    glGenVertexArrays(1, &this->_vao_guid);
    glGenBuffers(1, &this->_vbo_guid);

    glBindVertexArray(this->_vao_guid);
    glBindBuffer(GL_ARRAY_BUFFER, this->_vbo_guid);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), (GLvoid*)sizeof(glm::vec3));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void PrimitiveObject::draw(glm::mat4 proj_view) const
{
    this->program.use();
    this->program.set_uniform("proj_view", proj_view);
    this->program.set_uniform("model", global);

    glBindVertexArray(this->_vao_guid);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}
