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
#include <ShaderProgram.h>

bool press_keys[1024];

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key >= 0 && key < 1024)
    {
        press_keys[key] = action != GLFW_RELEASE;
    }
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

    glEnable(GL_DEPTH_TEST);

    ResourceStorage<Shader> storage;
    storage.emplace("s_vert", GL_VERTEX_SHADER,   "./resource/shader/vertex.glsl");
    storage.emplace("s_frag", GL_FRAGMENT_SHADER, "./resource/shader/fragment.glsl");

    storage.emplace("color_vert", GL_VERTEX_SHADER,   "./resource/shader/vertex_with_color.glsl");
    storage.emplace("color_frag", GL_FRAGMENT_SHADER, "./resource/shader/fragment_with_color.glsl");

    ResourceStorage<Model> models;
    models.emplace("ball", "./resource/model/ball.dae");

    ShaderProgram shader_program0(storage.get("s_vert"), storage.get("s_frag"));
    shader_program0.load();
    ShaderProgram shader_program1(storage.get("color_vert"), storage.get("color_frag"));
    shader_program1.load();

    Camera camera;

    std::vector<std::unique_ptr<AbstractObject>> objects;
    objects.emplace_back(new PrimitiveObject(shader_program1));
    objects.emplace_back(new PrimitiveObject(shader_program1, glm::translate(glm::mat4(1), glm::vec3(5, 2, 5))));
    objects.emplace_back(new ModelObject(shader_program0, models.get("ball")));
    objects.emplace_back(new ModelObject(shader_program0, models.get("ball"), glm::translate(glm::mat4(1), glm::vec3(5, 2, 5))));
    objects.emplace_back(new ModelObject(shader_program0, models.get("ball"), glm::scale(
            glm::translate(glm::mat4(1), glm::vec3(5, 2, 5)),
            glm::vec3(2)
    )));
    objects.emplace_back(new ModelObject(shader_program0, models.get("ball"), glm::scale(
            glm::translate(glm::mat4(1), glm::vec3(5, 2, 5)),
            glm::vec3(4)
    )));

    glfwSetKeyCallback(window, key_callback);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        camera.key_callback(press_keys);

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
    return 0;
}