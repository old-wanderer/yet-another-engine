//
// Created by Андрей on 16.10.17.
//

#include "AbstractObject.h"

AbstractObject::AbstractObject(ShaderProgram& program):
        program(program), _vao_guid(0) { }

AbstractObject::AbstractObject(ShaderProgram &program, glm::mat4 &&global):
        program(program), global(global), _vao_guid(0) { }

AbstractObject::~AbstractObject()
{
    glDeleteVertexArrays(1, &this->_vao_guid);
}
