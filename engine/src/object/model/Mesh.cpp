//
// Created by Андрей on 20.11.2017.
//

#include <iostream>
#include "common/utils.h"
#include "engine/Mesh.h"

Mesh::Mesh(): _vao_guid(0), _vbo_guid(0), _ebo_guid(0) { }

void Mesh::load()
{
    if (this->_isLoaded) return;

    glGenVertexArrays(1, &this->_vao_guid);
    glGenBuffers(1, &this->_vbo_guid);
    glGenBuffers(1, &this->_ebo_guid);

    glBindVertexArray(this->_vao_guid);
    glBindBuffer(GL_ARRAY_BUFFER, this->_vbo_guid);
    // TODO: передавть всегда vertex избыточно, так как все зависит от шейда и например цвет ему передавать не нужно

    size_t pack_size;
    void* pack_vertices = drop_unnecessary_data(&_vertices[0], _vertices.size(), sizeof(glm::vec3), sizeof(glm::vec3),
                            sizeof(vertex), pack_size);
    size_t elem_size = sizeof(vertex) - sizeof(vertex::color);

    glBufferData(GL_ARRAY_BUFFER, pack_size, pack_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ebo_guid);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), &_indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, static_cast<GLsizei>(elem_size), nullptr);

//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)sizeof(vertex::coordinate));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, static_cast<GLsizei>(elem_size), (GLvoid*)(sizeof(vertex::coordinate)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    this->_isLoaded = true;
}

void Mesh::unload()
{
    this->_isLoaded = false;
    glDeleteBuffers(1, &this->_ebo_guid);
    glDeleteBuffers(1, &this->_vbo_guid);
    glDeleteVertexArrays(1, &this->_vao_guid);
}

void Mesh::draw() const
{
    if (this->_texture)
        glBindTexture(GL_TEXTURE_2D, this->_texture->guid());
    glBindVertexArray(this->_vao_guid);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(_indices.size()), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}


