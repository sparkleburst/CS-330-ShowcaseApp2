#version 330 core

out vec4 FragColor;
in vec4 vertexColor;
in vec2 texCoord;

uniform sampler2D tex0;    // GL_TEXTURE0
uniform sampler2D tex1;    // GL_TEXTURE1
uniform sampler2D tex2;    // GL_TEXTURE2
// continue in this form as you add more textures

void main() {
    //FragColor = mix(texture(tex0, texCoord), texture(tex1, texCoord), 0.5) * vertexColor;

    vec4 textureColor = texture(tex0, texCoord);
    FragColor = textureColor * vec4(vertexColor);
    // the number (in blue) is the weight of how much the second texture can be seen compared to the first
    // * vertexColor means we can tint our object to be how we want it colorwise

    // FragColor = vec4(vertexColor.xy, 1.f, 1.f); // adds blue to everything
    // FragColor = vec4(vertexColor.x, vertexColor.y, 0.0, 1.0); // Set blue component to 0
}

// FragColor is making the color of the vertices and combining textures