#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color; // ignore
layout (location = 2) in vec2 in_texture_position;

out vec2 texture_position;

uniform mat4 proj_view;
uniform mat4 model;

void main()
{
    gl_Position = proj_view * model * vec4(position, 1.0);
    texture_position = in_texture_position;
}