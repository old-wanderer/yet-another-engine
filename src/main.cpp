//
// Created by Андрей on 15.10.17.
//

#include <GL/glew.h>

#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>

#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <ResourceStorage.h>
#include <Shader.h>
#include <ShaderProgram.h>
#include <Model.h>
#include <Camera.h>
#include <AbstractObject.h>
#include <ModelBuilder.h>
#include <Texture.h>
#include <TexturedModel.h>
#include <ObjectBuilder.h>

bool press_keys[1024];

void key_callback(GLFWwindow* window, int key, int, int action, int)
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
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    ResourceStorage<Shader> storage;
    storage.emplace("s_vert", GL_VERTEX_SHADER,   "./resource/shader/vertex.glsl");
    storage.emplace("s_frag", GL_FRAGMENT_SHADER, "./resource/shader/fragment.glsl");

    storage.emplace("color_vert", GL_VERTEX_SHADER,   "./resource/shader/vertex_with_color.glsl");
    storage.emplace("color_frag", GL_FRAGMENT_SHADER, "./resource/shader/fragment_with_color.glsl");

    storage.emplace("texture_vert", GL_VERTEX_SHADER,   "./resource/shader/vertex_with_texture.glsl");
    storage.emplace("texture_frag", GL_FRAGMENT_SHADER, "./resource/shader/fragment_with_texture.glsl");

    ShaderProgram shader_program0(storage.get("s_vert"), storage.get("s_frag"));
    shader_program0.load();
    ShaderProgram shader_program1(storage.get("color_vert"), storage.get("color_frag"));
    shader_program1.load();
    ShaderProgram shader_program2(storage.get("texture_vert"), storage.get("texture_frag"));
    shader_program2.load();

    ResourceStorage<Texture> textures;
    textures.emplace("bricks", "./resource/texture/bricks.png");
    textures.emplace("illuminati", "./resource/texture/test1.png");

    ResourceStorage<Model> models;
    models.emplace("ball",
                   ModelBuilder()
                           .setProgram(shader_program0)
                           .import_from_file("./resource/model/ball.dae")
                           .build()
    );
    models.emplace("cube",
                   ModelBuilder()
                           .setProgram(shader_program1)
                           .import_from_file("./resource/model/cube-purple.dae")
                           .set_color_vertex(1, glm::vec3(.1f, 1.f, .1f))
                           .build()
    );
    models.emplace("rect",
                   ModelBuilder()
                           .setProgram(shader_program1)
                           .push_back_vertex(glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(.1f, .9f, .1f))
                           .push_back_vertex(glm::vec3(-0.5f, 0.0f,  0.5f))
                           .push_back_vertex(glm::vec3( 0.5f, 0.0f, -0.5f))
                           .push_back_vertex(glm::vec3( 0.5f, 0.0f,  0.5f))
                           .push_back_all_indices({ 0, 1, 2, 1, 2, 3})
                           .build()
    );
    models.emplace("bricks", static_cast<Model*>(new TexturedModel(shader_program2, textures.get("bricks"))));
    models.emplace("illuminati", static_cast<Model*>(new TexturedModel(shader_program2, textures.get("illuminati"))));

    Camera camera;

    std::vector<std::unique_ptr<AbstractObject>> objects;
    objects.emplace_back(new AbstractObject(models.get("rect"), glm::scale(
            glm::translate(glm::mat4(1), glm::vec3(5, -2, 5)),
            glm::vec3(15)
    )));
    objects.emplace_back(new AbstractObject(models.get("ball")));
    objects.emplace_back(new AbstractObject(models.get("ball"), glm::translate(glm::mat4(1), glm::vec3(5, 2, 5)), false));
    objects.emplace_back(new AbstractObject(models.get("ball"), glm::scale(
            glm::translate(glm::mat4(1), glm::vec3(5, 2, 5)),
            glm::vec3(2)
    ), false));
    objects.emplace_back(new AbstractObject(models.get("ball"), glm::scale(
            glm::translate(glm::mat4(1), glm::vec3(5, 2, 5)),
            glm::vec3(4)
    ), false));
    objects.emplace_back(new AbstractObject(models.get("cube"), glm::translate(glm::mat4(1), glm::vec3(-5, 0, 0))));

    ObjectBuilder brick_wall_builder = ObjectBuilder().model(models.get("bricks")).scale(10);
    objects.emplace_back(brick_wall_builder.translate(glm::vec3(10,  2,  13)).build());
    objects.emplace_back(brick_wall_builder.translate(glm::vec3(10,  0, -10)).build());
    objects.emplace_back(brick_wall_builder.translate(glm::vec3( 0,  0, -10)).build());
    objects.emplace_back(brick_wall_builder.translate(glm::vec3( 0, 10, -10)).build());

    objects.emplace_back(ObjectBuilder()
                                 .model(models.get("illuminati"))
                                 .translate(glm::vec3(-10, 2, 13))
                                 .scale(10)
                                 .build()
    );

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