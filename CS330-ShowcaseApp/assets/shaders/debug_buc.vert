#version 330 core

layout (location = 0) in vec3 position;  // Assuming location 0 is for position
layout (location = 1) in vec3 color;     // Assuming location 1 is for color

out vec4 vertexColor;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

void main() {
    gl_Position = projection * view * model *vec4(position, 1);
    vertexColor = vec4(color, 1.0f);
}
