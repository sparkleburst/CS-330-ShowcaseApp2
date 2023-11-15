#version 330 core

out vec4 FragColor;
in vec4 vertexColor;

void main() {
    FragColor = vertexColor;
    // FragColor = vec4(vertexColor.xy, 1.f, 1.f); // adds blue to everything
    // FragColor = vec4(vertexColor.x, vertexColor.y, 0.0, 1.0); // Set blue component to 0
}

// FragColor is making the color of the vertices