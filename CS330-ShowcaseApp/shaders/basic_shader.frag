#version 330 core

out vec4 FragColor;
in vec4 vertexColor;

void main() {
    FragColor = vec4(vertexColor.xy, 1.f, 1.f);
}

// FragColor is making the color of the vertices