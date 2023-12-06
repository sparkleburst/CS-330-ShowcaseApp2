//
// Created by maxan on 12/3/2023.
//

#include <light.h>

Light::Light() {
    createShader();
    createMesh();
}

void Light::Init() {

}

void Light::Update(float deltaTime) {

}

void Light::Draw(const glm::mat4 &view, const glm::mat4 &projection) {
for (auto& model : _models) {
    auto* shader = model.GetShader();
    auto* mesh = model.GetMesh();
    shader->Bind();
    shader->SetMat4("projection", projection);
    shader->SetMat4("view", view);
    shader->SetMat4("model", Transform * mesh->Transform);

    mesh->Draw();
}

}

void Light::createShader() {
    _basicUnlitShader = std::make_shared<Shader>(Path("basic_unlit_color.vert"),
                                                 Path("basic_unlit_color.frag"));
}

void Light::createMesh() {
    auto cube = std::make_shared<Mesh>(Shapes::cubeVertices, Shapes::cubeElements,
                                         glm::vec3(1.f, 1.f, 1.f));
    auto& cubeModel = _models.emplace_back(cube, _basicUnlitShader);
}
