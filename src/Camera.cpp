//
// Created by Андрей on 20.10.17.
//

#include <cstdio>
#include "Camera.h"

void Camera::key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    if (action == GLFW_PRESS)
    {
        glm::vec3 direction;
        GLfloat speed = 0.1f;

        switch (key)
        {
            case GLFW_KEY_W: direction =  front; break;
            case GLFW_KEY_S: direction = -front; break;
            case GLFW_KEY_A: direction = glm::cross(up, front); break;
            case GLFW_KEY_D: direction = glm::cross(front, up); break;
            case GLFW_KEY_Q:
                yaw -= 2.f;
                front.x = cos(glm::radians(yaw));
                front.z = sin(glm::radians(yaw));
                return;
            case GLFW_KEY_E:
                yaw += 2.f;
                front.x = cos(glm::radians(yaw));
                front.z = sin(glm::radians(yaw));
                return;
            default: break;
        }

        position += speed * glm::normalize(direction);
        printf("position: %.4f %.4f %.4f\n", position.x, position.y, position.z);
    }
}

const glm::mat4 Camera::projection_view() const
{
//    glm::mat4 projection = glm::ortho(-3.f, 3.f,
//                                      -3.f, 3.f,
//                                      -3.f, 3.f);
    glm::mat4 projection = glm::perspective(45.0f, 1.f, 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(position, position + front, up);
    return projection * view;
}
