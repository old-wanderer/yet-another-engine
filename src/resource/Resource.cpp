//
// Created by Андрей on 16.10.17.
//

#include "Resource.h"

Resource::Resource(): _isLoaded(false), _guid(0) { }

bool Resource::isLoaded() const
{
    return this->_isLoaded;
}

GLuint Resource::guid() const
{
    return this->_guid;
}
