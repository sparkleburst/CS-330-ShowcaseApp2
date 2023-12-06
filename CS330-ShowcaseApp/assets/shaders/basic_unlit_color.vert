#version 330 core

out vec4 vertexColor;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

void main() {
    gl_Position = projection * view * model *vec4(position, 1);
    vertexColor = vec4(color, 1.0f);
}
