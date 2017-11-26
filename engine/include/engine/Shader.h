//
// Created by Андрей on 16.10.17.
//

#ifndef YET_ANOTHER_ENGINE_SHADER_HPP
#define YET_ANOTHER_ENGINE_SHADER_HPP

#include <string>
#include <GL/glew.h>
#include "Resource.h"

class Shader final: public Resource<ShaderLoadContext>
{
public:
    Shader(GLenum, std::string);
    void load() override;
    void unload() override;
};

#endif //YET_ANOTHER_ENGINE_SHADER_HPP
