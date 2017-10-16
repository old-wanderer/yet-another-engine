//
// Created by Андрей on 15.10.17.
//

#include <GL/glew.h>

#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>

#include <iostream>
#include <PrimitiveObject.h>

#include <fstream>


const std::string& read_file(const char* path)
{
    std::ifstream is(path);
    const std::string data((std::istreambuf_iterator<char>(is)), std::istreambuf_iterator<char>());
    is.close();

    return data;
}

GLuint create_shader(GLenum type, const char* path)
{
    const GLchar* code = read_file(path).c_str();

    GLuint guid = glCreateShader(type);
    glShaderSource(guid, 1, &code, nullptr);
    glCompileShader(guid);

    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(guid, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(guid, 512, nullptr, infoLog);
        std::string msg = "ERROR::SHADER::COMPILATION_FAILED";
        msg += infoLog;
        throw std::runtime_error(msg);
    }

    return guid;
}

int main()
{
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(640, 640, "test", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        printf("Error: %s\n", glewGetErrorString(err));
        return -1;
    }

    glGetError();

    PrimitiveObject object;

    GLuint vertex_shader = create_shader(GL_VERTEX_SHADER, "./resource/shader/vertex.glsl");
    GLuint fragme_shader = create_shader(GL_FRAGMENT_SHADER, "./resource/shader/fragment.glsl");

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertex_shader);
    glAttachShader(shaderProgram, fragme_shader);
    glLinkProgram(shaderProgram);

    glUseProgram(shaderProgram);
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        object.draw();

        glfwSwapBuffers(window);
    }


    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}