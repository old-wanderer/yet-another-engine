//
// Created by Андрей on 20.10.17.
//

#include "Camera.h"

Camera::Camera()
{
    handlers.emplace_back(GLFW_KEY_W, [this] {
        this->position += speed * front;
    });
    handlers.emplace_back(GLFW_KEY_S, [this] {
        this->position -= speed * front;
    });
    handlers.emplace_back(GLFW_KEY_A, [this] {
        this->position += speed * glm::normalize(glm::cross(up, front));
    });
    handlers.emplace_back(GLFW_KEY_D, [this] {
        this->position += speed * glm::normalize(glm::cross(front, up));
    });
    handlers.emplace_back(GLFW_KEY_Q, [this] {
        this->yaw -= 2.f;
        this->front.x = cos(glm::radians(yaw));
        this->front.z = sin(glm::radians(yaw));
    });
    handlers.emplace_back(GLFW_KEY_E, [this] {
        this->yaw += 2.f;
        this->front.x = cos(glm::radians(yaw));
        this->front.z = sin(glm::radians(yaw));
    });
}

const glm::mat4 Camera::projection_view() const
{
    glm::mat4 projection = glm::perspective(45.0f, 1.f, 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(position, position + front, up);
    return projection * view;
}

void Camera::key_callback(const bool press_keys[1024])
{
    for (auto& pair: handlers)
    {
        if (press_keys[pair.first])
        {
            pair.second();
        }
    }
}
