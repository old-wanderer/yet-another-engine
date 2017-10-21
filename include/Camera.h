//
// Created by Андрей on 20.10.17.
//

#ifndef YET_ANOTHER_ENGINE_CAMERA_H
#define YET_ANOTHER_ENGINE_CAMERA_H

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
    Camera() = default;

    void key_callback(GLFWwindow*, int, int, int, int);

    const glm::mat4 projection_view() const;
protected:
    glm::vec3 position = { 0.f, 0.f,  5.f};
    glm::vec3 front    = glm::normalize(glm::vec3(0.f, 0.f, -1.f));
    glm::vec3 up       = { 0.f, 1.f,  0.f};

    GLfloat yaw = -90.f;
};




#endif //YET_ANOTHER_ENGINE_CAMERA_H
