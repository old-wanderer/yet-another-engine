#version 330 core

layout (location = 0) in vec3 position;

uniform mat4 proj_view;

void main()
{
    gl_Position = proj_view * vec4(position, 1.0);
}