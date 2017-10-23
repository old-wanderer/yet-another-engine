//
// Created by Андрей on 23.10.17.
//

#ifndef YET_ANOTHER_ENGINE_SHADERPROGRAM_H
#define YET_ANOTHER_ENGINE_SHADERPROGRAM_H


#include <map>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

class ShaderProgram: public Resource
{
public:
    ShaderProgram(Shader&, Shader&);

    void use();

    void load() override;
    void unload() override;

    void set_uniform(const std::string&, const glm::mat4&);

protected:
    Shader& vertex;
    Shader& fragment;

    std::map<std::string, GLint> uniform_guides;
};


#endif //YET_ANOTHER_ENGINE_SHADERPROGRAM_H
