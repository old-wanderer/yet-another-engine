//
// Created by Андрей on 15.11.2017.
//

#include <GL/glew.h>

#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>

#include "engine/Scene3D.h"

Scene3D::Scene3D()
{
    register_listener(GLFW_KEY_ESCAPE, new Listener<Scene3D>(*this, [](Scene3D& scene) { glfwSetWindowShouldClose(scene.window, GL_TRUE); }));
}

void Scene3D::emplace_object(AbstractObject *object)
{
    objects.emplace_back(std::shared_ptr<AbstractObject>(object));
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

    glfwSetKeyCallback(window, Scene3D::key_callback);
}

void Scene3D::start()
{
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        for (auto& pair: listeners)
        {
            if (press_keys[pair.first])
            {
                pair.second->apply();
            }
        }

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 trans = _camera.projection_view();

        // todo что-то мне кажется, что так будет эффективнее, надо разобраться и выбрать одно
        // using namespace std::placeholders;
        // std::for_each(objects.begin(), objects.end(), std::bind(&AbstractObject::draw, _1, trans));
        for (auto& object: objects)
        {
            object->draw(trans);
        }

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

void Scene3D::register_listener(short key, BaseListener *listener)
{
    listeners.emplace_back(key, std::unique_ptr<BaseListener>(listener));
}

void Scene3D::key_callback(GLFWwindow*, int key, int, int action, int)
{
    if (key >= 0 && key < 1024)
    {
        CURRENT_SCENE3D.press_keys[key] = action != GLFW_RELEASE;
    }
}

Camera &Scene3D::camera()
{
    return _camera;
}

std::shared_ptr<AbstractObject> Scene3D::get_object(uint32_t index)
{
    return objects[index];
}
