#version 330 core
    layout (location = 0) in vec3 position;
    layout (location = 1) in vec3 color;
    layout (location = 2) in vec3 normal;
    layout (location = 3) in vec2 uv;

    out vec3 FragPos; // Fragment position in world space
    out vec3 Normal; // Normal in world space
    out vec3 FragColor; // Vertex color
    out vec2 TexCoords; // Texture coordinates

    uniform mat4 view;
    uniform mat4 projection;
    uniform mat4 model;

    void main() {
        gl_Position = projection * view * model * vec4(position, 1);
        FragColor = color;
        TexCoords = uv;
        Normal = normal;
        FragPos = vec3(model * vec4(position, 1.0));
        // vertexColor = vec4(0.0f, 0.0f, 0.0f, 1.0f); // Black
    }

    // if you change something here go into shader.cpp and add a space or return there somewhere
    // for the program to realize a change has been made

