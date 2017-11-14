//
// Created by Андрей on 15.11.2017.
//

#include <GL/glew.h>

#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>

#include "Scene3D.h"

void Scene3D::emplace_object(AbstractObject *object)
{
    objects.emplace_back(std::unique_ptr<AbstractObject>(object));
}

void Scene3D::init()
{
    if (!glfwInit())
        throw std::logic_error("glfw init error");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(640, 640, "test", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        throw std::logic_error("glfw cant create window");
    }

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        throw std::logic_error((char*)glewGetErrorString(err));
    }

    glGetError();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Scene3D::start()
{
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
//        camera.key_callback(press_keys);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 trans = camera.projection_view();
        for (auto& object: objects)
        {
            object->draw(trans);
        }

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}
