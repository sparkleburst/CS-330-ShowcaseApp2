#version 330 core

out vec4 FragColor;

in vec4 vertexColor;
in vec3 fragNormal;
in vec3 fragPosition;
in vec2 texCoord;

// in vec2 texCoord;

uniform vec3 lightPos0;
uniform vec3 lightPos1;
uniform sampler2D tex0;

void main() {
    vec3 objectColor = texture(tex0, texCoord).rgb;

    vec3 lightColor = vec3(1.f, 1.f, 1.f);

    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;


    // diffuse color
    vec3 norm = normalize(fragNormal);
    vec3 lightDir = normalize(lightPos0 - fragPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 finalColor = (diffuse + ambient) * objectColor;
    FragColor = vec4(finalColor, 1.0);
}
