//
// Created by Андрей on 20.10.17.
//

#include <common/Exceptions.h>
#include "engine/Camera.h"

const glm::mat4 Camera::projection_view() const
{
    glm::mat4 projection = glm::perspective(45.0f, 1.f, 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(position, position + front, up);
    return projection * view;
}

void Camera::move_x_axis(float offset)
{
    this->position += offset * glm::normalize(glm::cross(up, front));
}

void Camera::move_y_axis(float)
{
    NOT_IMPLEMENTED;
}

void Camera::move_z_axis(float offset)
{
    this->position += offset * front;
}

void Camera::move_yaw(float angle)
{
    this->yaw += angle;
    this->front.x = cos(glm::radians(yaw));
    this->front.z = sin(glm::radians(yaw));
}

void Camera::move_roll(float)
{
    NOT_IMPLEMENTED;
}

void Camera::move_pitch(float)
{
    NOT_IMPLEMENTED;
}
