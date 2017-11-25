//
// Created by Андрей on 16.10.17.
//

#ifndef YET_ANOTHER_ENGINE_RESOURCE_H
#define YET_ANOTHER_ENGINE_RESOURCE_H


#include <GL/glew.h>
#include <common/Exceptions.h>
#include "Enums.h"

// Пока еще не уверен в затее с LoadContext
struct LoadContext {};
struct PathLoadContext {
    std::string path;
};
// Надо наследоваться от PathLoadContext
struct ShaderLoadContext {
    GLenum type;
    std::string path;
};
struct MeshLoadContext {
    uint32_t inputs;
};

template <typename T = LoadContext>
class Resource
{
public:
    template<typename T1 = T>
    explicit Resource(typename std::enable_if<std::is_base_of<LoadContext, T1>::value>::type * = nullptr): _isLoaded(false), _guid(0) {};
    explicit Resource(T load): loadContext(load), _isLoaded(false), _guid(0) {};
    virtual ~Resource() = default;

    virtual void load() = 0;
    virtual void unload() = 0;

    bool isLoaded() const { return _isLoaded; } ;
    GLuint guid() const { return _guid; }

    T loadContext; // TODO найти способ спрятать в protected
protected:

    bool _isLoaded;
    GLuint _guid;
};


#endif //YET_ANOTHER_ENGINE_RESOURCE_H
