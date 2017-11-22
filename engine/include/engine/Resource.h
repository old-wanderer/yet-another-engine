//
// Created by Андрей on 16.10.17.
//

#ifndef YET_ANOTHER_ENGINE_RESOURCE_H
#define YET_ANOTHER_ENGINE_RESOURCE_H


#include <GL/glew.h>
#include <common/Exceptions.h>

class Resource
{
public:
    Resource();
    virtual ~Resource() = default;

    virtual void load() = 0;
    virtual void unload() = 0;

    bool isLoaded() const;
    GLuint guid() const;
protected:
    bool _isLoaded;
    GLuint _guid;
};


#endif //YET_ANOTHER_ENGINE_RESOURCE_H
