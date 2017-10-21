//
// Created by Андрей on 15.10.17.
//

#include <GL/glew.h>

#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>

#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <PrimitiveObject.h>
#include <ResourceStorage.h>
#include <Shader.h>
#include <Model.h>
#include <ModelObject.h>
#include <Camera.h>

Camera camera;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    camera.key_callback(window, key, scancode, action, mode);
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

    ResourceStorage<Shader> storage;
    storage.emplace("s_vert", GL_VERTEX_SHADER,   "./resource/shader/vertex.glsl");
    storage.emplace("s_frag", GL_FRAGMENT_SHADER, "./resource/shader/fragment.glsl");

    ResourceStorage<Model> models;
    models.emplace("ball", "./resource/model/ball.dae");

    PrimitiveObject object;
    ModelObject model_object(models.get("ball"));

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, storage.get("s_vert").guid());
    glAttachShader(shaderProgram, storage.get("s_frag").guid());
    glLinkProgram(shaderProgram);

    glUseProgram(shaderProgram);

    GLint transformLoc = glGetUniformLocation(shaderProgram, "proj_view");

    glfwSetKeyCallback(window, key_callback);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glm::mat4 trans = camera.projection_view();
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

        model_object.draw();

        glfwSwapBuffers(window);
    }


    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}