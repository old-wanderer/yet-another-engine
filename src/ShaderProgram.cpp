//
// Created by Андрей on 23.10.17.
//

#include <iostream>

#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(Shader &vertex, Shader &fragment):
        vertex(vertex), fragment(fragment) { }

void ShaderProgram::use()
{
    glUseProgram(this->_guid);
}

void ShaderProgram::load()
{
    this->_guid = glCreateProgram();
    // TODO проверку на загруженность шейдеров, а лучше сделать через листнеров
    glAttachShader(this->_guid, vertex.guid());
    glAttachShader(this->_guid, fragment.guid());
    glLinkProgram(this->_guid);

    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(this->_guid, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(this->_guid, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
}

void ShaderProgram::unload()
{

}

void ShaderProgram::set_uniform(const std::string &name, const glm::mat4 &value)
{
    auto point = uniform_guides.find(name);
    GLint loc;
    if (point == uniform_guides.end())
    {
        loc = glGetUniformLocation(this->_guid, name.c_str());
        if (loc < 0)
        {
            throw std::out_of_range("cant find uniform");
        }
    } else {
        loc = point->second;
    }

    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
}
