//
// Created by Андрей on 19.11.2017.
//

#include <engine/Scene3D.h>
#include <engine/ResourceStorage.h>
#include <engine/ObjectBuilder.h>
#include <engine/ModelBuilder.h>

int main()
{
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

    ResourceStorage<Model> models;
    models.emplace("king", ModelBuilder()
            .setProgram(shader_program2)
            .import_from_file("./resource/model/king.obj")
            .build());

    scene.emplace_object(ObjectBuilder()
                                 .model(models.get("king"))
                                 .scale(glm::vec3(.5f))
                                 .rotate(135, glm::vec3(0.f, 1.f, 0.f))
                                 .build());
    scene.start();
    return 0;
}
