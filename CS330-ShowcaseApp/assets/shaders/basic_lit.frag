#version 330 core

out vec4 FragColor;

in vec4 vertexColor;
in vec3 fragNormal;
in vec3 fragPosition;

// in vec2 texCoord;

uniform vec3 lightPos0;
uniform vec3 lightPos1;

void main() {
    vec3 objectColor = vertexColor.xyz;

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


/*
// Material properties
struct Material {
    vec3 ambient;
    vec3 specular;
    float shininess;
};

// Light properties
struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos; // Fragment position in world space
in vec3 Normal; // Normal in world space
in vec3 FragColor; // Vertex color
in vec2 TexCoords; // Texture coordinates

out vec4 FinalColor;

uniform Material material;
uniform Light light100;
uniform Light light10;
uniform vec3 viewPos;
uniform sampler2D textureSampler;

void main() {

    // Ambient lighting
    vec3 ambient = material.ambient * (light100.ambient + light10.ambient);

    // Diffuse lighting
    vec3 norm = normalize(Normal);
    vec3 lightDir1 = normalize(light100.position - FragPos);
    vec3 lightDir2 = normalize(light10.position - FragPos);
    float diff1 = max(dot(norm, lightDir1), 0.0);
    float diff2 = max(dot(norm, lightDir2), 0.0);
    //vec3 baseColor = texture(textureSampler, TexCoords).rgb;
    vec3 baseColor = vec3(1.0, 1.0, 1.0);
    vec3 diffuse = FragColor.rgb * baseColor * (light100.diffuse * diff1 + light10.diffuse * diff2);

    // Specular lighting
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir1 = reflect(-lightDir1, norm);
    vec3 reflectDir2 = reflect(-lightDir2, norm);
    float spec1 = pow(max(dot(viewDir, reflectDir1), 0.0), material.shininess);
    float spec2 = pow(max(dot(viewDir, reflectDir2), 0.0), material.shininess);
    vec3 specular = material.specular * (light100.specular * spec1 + light10.specular * spec2);

    vec3 result = ambient + diffuse + specular;
    FinalColor = vec4(result, 1.0);

}

*/