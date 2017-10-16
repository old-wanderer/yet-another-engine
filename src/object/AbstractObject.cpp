//
// Created by Андрей on 16.10.17.
//

#include "AbstractObject.h"

AbstractObject::AbstractObject(): _vao_guid(0) { }

AbstractObject::~AbstractObject()
{
    glDeleteVertexArrays(1, &this->_vao_guid);
}