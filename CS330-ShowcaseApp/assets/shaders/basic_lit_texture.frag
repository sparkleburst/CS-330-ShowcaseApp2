#version 330 core

out vec4 FragColor;

in vec4 vertexColor;
in vec3 fragNormal;
in vec3 fragPosition;
in vec2 texCoord;

// in vec2 texCoord;
uniform vec3 eyePos;

uniform vec3 lightPos0;
uniform vec3 lightPos1;
uniform sampler2D tex0;

void main() {
    vec3 objectColor = texture(tex0, texCoord).rgb;

    vec3 lightColorAmbient = vec3(1.f, 1.f, 1.f);
    vec3 lightColor0 = vec3(0.5f, 0.5f, 0.5f);
    vec3 lightColor1 = vec3(0.1f, 0.1f, 0.1f);

    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColorAmbient;


    // diffuse color
    vec3 norm = normalize(fragNormal);
    vec3 lightDir0 = normalize(lightPos0 - fragPosition);
    vec3 lightDir1 = normalize(lightPos1 - fragPosition);

    float diff0 = max(dot(norm, lightDir0), 0.0);
    float diff1 = max(dot(norm, lightDir1), 0.0);

    vec3 diffuse0 = diff0 * lightColor0;
    vec3 diffuse1 = diff1 * lightColor1;

    /*
    // specular lighting
    float specularStrength = 1;
    float shininess = 256;

    vec3 viewDir = normalize(eyePos - fragPosition);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = specularStrength * spec * lightColor;
*/
    vec3 finalColor = (diffuse0 + diffuse1 + ambient) * objectColor;
    //vec3 finalColor = (diffuse0 + diffuse1 + ambient + specular) * objectColor;
    FragColor = vec4(finalColor, 1.0);
}
