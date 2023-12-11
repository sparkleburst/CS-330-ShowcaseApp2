#version 330 core

out vec4 FragColor;

in vec4 vertexColor;
in vec3 fragNormal;
in vec3 fragPosition;

// in vec2 texCoord;
uniform vec3 eyePos;

uniform vec3 lightPos0;
uniform vec3 lightPos1;

void main() {
    vec3 objectColor = vertexColor.xyz;

    vec3 lightColor = vec3(1.f, 0.5f, 0.5f);

    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;


    // diffuse color
    vec3 norm = normalize(fragNormal);
    vec3 lightDir = normalize(lightPos0 - fragPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // specular lighting
    float specularStrength = 5;
    float shininess = 64;

    vec3 viewDir = normalize(eyePos - fragPosition);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 finalColor = (diffuse + ambient + specular) * objectColor;
    FragColor = vec4(finalColor, 1.0);
}


