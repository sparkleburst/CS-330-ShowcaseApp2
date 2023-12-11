//
// Created by maxan on 12/3/2023.
//

#include <light.h>
#include "shapes.h"
#include "glm/ext/matrix_transform.hpp"

Light::Light(float posMultiplier) {
    createShader();
    createMesh();

    _posMultiplier = posMultiplier;
}

void Light::Init() {

}

void Light::Update(float deltaTime) {
    auto cos = std::cos(_totalTime * .5f);
    auto sin = std::sin(_totalTime * .5f);

    Transform [3][0] = cos * _posMultiplier * 3.5f;
    Transform [3][1] = 2;
    Transform [3][2] = sin * _posMultiplier * 3.5f;

    _totalTime += deltaTime;
}

void Light::Draw(const SceneParameters& sceneParams) {
    for (auto& model : _models) {
        auto* shader = model.GetShader();
        auto* mesh = model.GetMesh();
        shader->Bind();
        shader->SetMat4("projection", sceneParams.ProjectionMatrix);
        shader->SetMat4("view", sceneParams.ViewMatrix);
        shader->SetMat4("model", Transform * mesh->Transform);

        mesh->Draw();
    }
}

void Light::ProcessLighting(SceneParameters &sceneParams) {

    if (sceneParams.Lights.size() < MAX_LIGHTS) {
        auto lightPos = glm::vec3(Transform[3]);
        sceneParams.Lights.emplace_back(lightPos);
    }

}

void Light::createShader() {
    _basicUnlitShader = std::make_shared<Shader>(Path("assets/shaders/basic_unlit_color.vert"),
                                                 Path("assets/shaders/basic_unlit_color.frag"));
}

void Light::createMesh() {
    auto lightCube = std::make_shared<Mesh>(Shapes::cubeVertices, Shapes::cubeElements,
                                         glm::vec3(1.f, 1.f, 1.f));
    _models.emplace_back(lightCube, _basicUnlitShader);
    lightCube->Transform = glm::scale(lightCube->Transform, glm::vec3(0.1f, 0.1f, 0.1f));
}


