//
// Created by Андрей on 18.11.2017.
//


#include <iostream>
#include <engine/Scene3D.h>
#include <engine/ResourceStorage.h>
#include <engine/Texture.h>
#include <engine/ModelBuilder.h>
#include <engine/TexturedModel.h>
#include <engine/ObjectBuilder.h>

int main() {
    Scene3D& scene = CURRENT_SCENE3D;
    scene.init();

    scene.register_key_callback(GLFW_KEY_W, [](Camera& camera) { camera.move_z_axis( .1f); });
    scene.register_key_callback(GLFW_KEY_S, [](Camera& camera) { camera.move_z_axis(-.1f); });
    scene.register_key_callback(GLFW_KEY_A, [](Camera& camera) { camera.move_x_axis( .1f); });
    scene.register_key_callback(GLFW_KEY_D, [](Camera& camera) { camera.move_x_axis(-.1f); });
    scene.register_key_callback(GLFW_KEY_Q, [](Camera& camera) { camera.move_yaw(-2.f); });
    scene.register_key_callback(GLFW_KEY_E, [](Camera& camera) { camera.move_yaw( 2.f); });
    scene.register_key_callback(GLFW_KEY_Z, [](Camera& camera) { camera.move_y_axis(2.f); });

    ResourceStorage<Shader> storage;
    storage.emplace("s_vert", GL_VERTEX_SHADER,   "../resource/shader/vertex.glsl");
    storage.emplace("s_frag", GL_FRAGMENT_SHADER, "../resource/shader/fragment.glsl");

    storage.emplace("color_vert", GL_VERTEX_SHADER,   "../resource/shader/vertex_with_color.glsl");
    storage.emplace("color_frag", GL_FRAGMENT_SHADER, "../resource/shader/fragment_with_color.glsl");

    storage.emplace("texture_vert", GL_VERTEX_SHADER,   "../resource/shader/vertex_with_texture.glsl");
    storage.emplace("texture_frag", GL_FRAGMENT_SHADER, "../resource/shader/fragment_with_texture.glsl");

    ShaderProgram shader_program0(storage.get("s_vert"), storage.get("s_frag"));
    shader_program0.load();
    ShaderProgram shader_program1(storage.get("color_vert"), storage.get("color_frag"));
    shader_program1.load();
    ShaderProgram shader_program2(storage.get("texture_vert"), storage.get("texture_frag"));
    shader_program2.load();

    ResourceStorage<Texture> textures;
    textures.emplace("bricks", "../resource/texture/bricks.png");
    textures.emplace("illuminati", "../resource/texture/test1.png");

    ResourceStorage<Model> models;
    models.emplace("ball",
                   ModelBuilder()
                           .setProgram(shader_program0)
                           .import_from_file("../resource/model/ball.dae")
                           .build()
    );
    models.emplace("cube",
                   ModelBuilder()
                           .setProgram(shader_program1)
                           .import_from_file("../resource/model/cube-purple.dae")
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

    scene.emplace_object(new AbstractObject(models.get("rect"), glm::scale(
            glm::translate(glm::mat4(1), glm::vec3(5, -2, 5)),
            glm::vec3(15)
    )));
    scene.emplace_object(new AbstractObject(models.get("ball")));
    scene.emplace_object(new AbstractObject(models.get("ball"), glm::translate(glm::mat4(1), glm::vec3(5, 2, 5)), false));
    scene.emplace_object(new AbstractObject(models.get("ball"), glm::scale(
            glm::translate(glm::mat4(1), glm::vec3(5, 2, 5)),
            glm::vec3(2)
    ), false));
    scene.emplace_object(new AbstractObject(models.get("ball"), glm::scale(
            glm::translate(glm::mat4(1), glm::vec3(5, 2, 5)),
            glm::vec3(4)
    ), false));
    scene.emplace_object(new AbstractObject(models.get("cube"), glm::translate(glm::mat4(1), glm::vec3(-5, 0, 0))));

    ObjectBuilder brick_wall_builder = ObjectBuilder().model(models.get("bricks")).scale(10);
    scene.emplace_object(brick_wall_builder.translate(glm::vec3(10,  2,  13)).build());
    scene.emplace_object(brick_wall_builder.translate(glm::vec3(10,  0, -10)).build());
    scene.emplace_object(brick_wall_builder.translate(glm::vec3( 0,  0, -10)).build());
    scene.emplace_object(brick_wall_builder.translate(glm::vec3( 0, 10, -10)).build());

    scene.emplace_object(ObjectBuilder()
                                 .model(models.get("illuminati"))
                                 .translate(glm::vec3(-10, 2, 13))
                                 .scale(10)
                                 .build()
    );

    scene.start();
    return 0;
}