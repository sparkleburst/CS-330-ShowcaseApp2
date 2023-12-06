//
// Created by maxan on 12/3/2023.
//

#pragma once

#include <game_object.h>
#include <shader.h>
#include <mesh.h>
#include <model.h>


class Light : public GameObject{
public:
    Light();

    void Init() override;

    void Update(float deltaTime) override;

    void Draw(const glm::mat4 &view, const glm::mat4 &projection) override;

private:
    void createShader();
    void createMesh();

private:
    std::shared_ptr<Shader> _basicUnlitShader {};
    std::shared_ptr<Mesh> _pyramid {};

    std::vector<Model> _models {};
};


