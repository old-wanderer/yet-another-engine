#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 in_color;

out vec3 vertex_color;

uniform mat4 proj_view;

void main()
{
    gl_Position = proj_view * vec4(position, 1.0);
    vertex_color = in_color;
}