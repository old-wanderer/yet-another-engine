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

    scene.register_listener(GLFW_KEY_W, new Listener<Camera>(scene.camera(), [](Camera& camera) { camera.move_z_axis( .1f); }));
    scene.register_listener(GLFW_KEY_S, new Listener<Camera>(scene.camera(), [](Camera& camera) { camera.move_z_axis(-.1f); }));
    scene.register_listener(GLFW_KEY_A, new Listener<Camera>(scene.camera(), [](Camera& camera) { camera.move_x_axis( .1f); }));
    scene.register_listener(GLFW_KEY_D, new Listener<Camera>(scene.camera(), [](Camera& camera) { camera.move_x_axis(-.1f); }));
    scene.register_listener(GLFW_KEY_Q, new Listener<Camera>(scene.camera(), [](Camera& camera) { camera.move_yaw(-2.f); }));
    scene.register_listener(GLFW_KEY_E, new Listener<Camera>(scene.camera(), [](Camera& camera) { camera.move_yaw( 2.f); }));
    scene.register_listener(GLFW_KEY_Z, new Listener<Camera>(scene.camera(), [](Camera& camera) { camera.move_y_axis(2.f); }));

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
    models.emplace("king",
                   ModelBuilder()
                           .setProgram(shader_program2)
                           .import_from_file("./resource/model/king.obj")
                           .build()
    );
    models.emplace("rect",
                   ModelBuilder()
                           .setProgram(shader_program1)
                           .begin_mesh(ShaderInputData::VERTEX | ShaderInputData::VERTEX_COLOR)
                               .push_back_vertex(glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(.1f, .9f, .1f))
                               .push_back_vertex(glm::vec3(-0.5f, 0.0f,  0.5f))
                               .push_back_vertex(glm::vec3( 0.5f, 0.0f, -0.5f))
                               .push_back_vertex(glm::vec3( 0.5f, 0.0f,  0.5f))
                               .push_back_all_indices({ 0, 1, 2, 1, 2, 3})
                           .end_mesh()
                           .build()
    );

    scene.emplace_object(ObjectBuilder()
                                 .model(models.get("king"))
                                 .scale(glm::vec3(.5f))
                                 .rotate(135, glm::vec3(0.f, 1.f, 0.f))
                                 .build()
    );
    scene.emplace_object(ObjectBuilder()
                                 .model(models.get("rect"))
                                 .scale(glm::vec3(15))
                                 .translate(glm::vec3(5, -2, 5))
                                 .build()
    );

    auto king = scene.get_object(0);
    typedef decltype(king) king_t;
    scene.register_listener(GLFW_KEY_UP,   new Listener<king_t>(king, [](king_t& king) { king->move(glm::vec3(.0f,  .2f, .0f)); }));
    scene.register_listener(GLFW_KEY_DOWN, new Listener<king_t>(king, [](king_t& king) { king->move(glm::vec3(.0f, -.2f, .0f)); }));

    scene.start();
    return 0;
}
