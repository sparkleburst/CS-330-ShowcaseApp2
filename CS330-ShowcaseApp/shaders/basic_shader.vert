#version 330 core
    layout (location = 0) in vec3 position;
    layout (location = 1) in vec3 color;
    layout (location = 2) in vec3 normal;
    layout (location = 3) in vec3 uv;

    out vec4 vertexColor;
    void main() {
        gl_Position = vec4(position.x, position.y, position.z, 1.0f);
        vertexColor = vec4(color, 1.0f);
    }

