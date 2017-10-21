//
// Created by Андрей on 20.10.17.
//

#ifndef YET_ANOTHER_ENGINE_CAMERA_H
#define YET_ANOTHER_ENGINE_CAMERA_H

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <functional>

class Camera
{
public:
    Camera();

    void key_callback(const bool[1024]);

    const glm::mat4 projection_view() const;
protected:
    glm::vec3 position = { 0.f, 0.f,  5.f};
    glm::vec3 front    = glm::normalize(glm::vec3(0.f, 0.f, -1.f));
    glm::vec3 up       = { 0.f, 1.f,  0.f};

    GLfloat yaw = -90.f;
    GLfloat speed = 0.1f;

    std::vector<std::pair<short, std::function<void()>>> handlers;
};




#endif //YET_ANOTHER_ENGINE_CAMERA_H
