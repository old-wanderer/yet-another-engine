//
// Created by Андрей on 20.11.2017.
//

#include <iostream>
#include "common/utils.h"
#include "engine/Mesh.h"

Mesh::Mesh(uint32_t inputs): Resource({inputs}), _vao_guid(0), _vbo_guid(0), _ebo_guid(0) {}

void Mesh::load()
{
    if (this->_isLoaded) return; // TODO дублировать эту херню не круто

    glGenVertexArrays(1, &this->_vao_guid);
    glGenBuffers(1, &this->_vbo_guid);
    glGenBuffers(1, &this->_ebo_guid);

    glBindVertexArray(this->_vao_guid);
    glBindBuffer(GL_ARRAY_BUFFER, this->_vbo_guid);

    const auto fields = vertex::fields;

    size_t current_vertex_offset = 0;
    size_t vertex_data_size = sizeof(vertex);
    size_t raw_vertex_data_size = _vertices.size() * vertex_data_size;
    void* raw_vertex_data = std::malloc(raw_vertex_data_size);
    std::memcpy(raw_vertex_data, &_vertices[0], raw_vertex_data_size);

    for (uint32_t i = 0; i < fields.size(); i++)
    {
        if (loadContext.inputs & 1 << i)
        {
            current_vertex_offset += fields[i];
        } else {
            void* prev_data = raw_vertex_data; // TODO на самом деле можно не выделять новую память
            raw_vertex_data_size = _vertices.size() * (vertex_data_size - fields[i]);
            raw_vertex_data = drop_unnecessary_data(
                    raw_vertex_data,
                    _vertices.size(),
                    current_vertex_offset,
                    fields[i],
                    vertex_data_size
            );
            vertex_data_size -= fields[i];
            std::free(prev_data);
        }
    }

    glBufferData(GL_ARRAY_BUFFER, raw_vertex_data_size, raw_vertex_data, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ebo_guid);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), &_indices[0], GL_STATIC_DRAW);

    current_vertex_offset = 0;
    uint32_t layout_num = 0;
    for (uint32_t i = 0; i < fields.size(); i++)
    {
        if (loadContext.inputs & 1 << i)
        {
            glEnableVertexAttribArray(layout_num);
            glVertexAttribPointer(
                    layout_num,
                    static_cast<GLint>(fields[i] / sizeof(GLfloat)),
                    GL_FLOAT,
                    GL_FALSE,
                    static_cast<GLsizei>(vertex_data_size),
                    (GLvoid*) current_vertex_offset
            );
            layout_num++;
            current_vertex_offset += fields[i];
        }
    }

    std::free(raw_vertex_data);

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


