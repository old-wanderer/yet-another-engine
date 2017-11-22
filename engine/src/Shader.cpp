//
// Created by Андрей on 16.10.17.
//

#include <fstream>
#include <iostream>
#include "engine/Shader.h"

Shader::Shader(GLenum type, std::string path): Resource({type, path}) {}

void Shader::load()
{
    if (this->_isLoaded) return;

    std::ifstream is(loadContext.path);
    std::string data((std::istreambuf_iterator<char>(is)), std::istreambuf_iterator<char>());
    is.close();
    const GLchar* code = data.c_str();

    this->_guid = glCreateShader(loadContext.type);
    glShaderSource(this->_guid, 1, &code, nullptr);
    glCompileShader(this->_guid);

    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(this->_guid, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(this->_guid, 512, nullptr, infoLog);
        std::string msg = "ERROR::SHADER::COMPILATION_FAILED";
        msg += infoLog;
        throw std::runtime_error(msg);
    }

    this->_isLoaded = true;
}

void Shader::unload()
{

}
