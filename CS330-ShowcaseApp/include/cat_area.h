//
// Created by maxan on 12/3/2023.
//

#pragma once
#include <game_object.h>
#include <model.h>
#include <shader.h>
#include <mesh.h>

class CatArea : public GameObject {
public:
    CatArea();
    void Init() override;
    void Update(float deltaTime) override;
    void Draw(const glm::mat4& view, const glm::mat4& projection) override;

private:
    void createShaders();

    void createCatBed();

    void createBall1();
    void createBall2();
    void createBall3();

    void createBlueToy();

    void createKickerToy();

    void createPyramid();

private:
    std::shared_ptr<Shader> _basicLitShader;
    std::shared_ptr<Shader> _textureShader;

    std::shared_ptr<Mesh> _cylinder;
    std::shared_ptr<Mesh> _cube;
    std::shared_ptr<Mesh> _pyramid;

    std::vector<Model> _models {};
};



