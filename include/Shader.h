//
// Created by Андрей on 16.10.17.
//

#ifndef YET_ANOTHER_ENGINE_SHADER_HPP
#define YET_ANOTHER_ENGINE_SHADER_HPP

#include <string>
#include <GL/glew.h>
#include "Resource.h"

class Shader final: public Resource
{
public:
    Shader(GLenum, const char*);
    void load() override;
    void unload() override;

private:
    GLenum _type;
    std::string _path_to_source;
};

#endif //YET_ANOTHER_ENGINE_SHADER_HPP
