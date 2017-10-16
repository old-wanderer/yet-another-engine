//
// Created by Андрей on 16.10.17.
//

#include "Resource.h"

Resource::Resource(): _isLoaded(false), _guid(0) { }

bool Resource::isLoaded()
{
    return this->_isLoaded;
}

GLuint Resource::guid()
{
    return this->_guid;
}
