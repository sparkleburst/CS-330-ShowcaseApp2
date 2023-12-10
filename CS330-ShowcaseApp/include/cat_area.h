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
    void Draw(const SceneParameters& sceneParams) override;

    void ProcessLighting(SceneParameters &sceneParams) override;

private:
    void createShaders();

    void createCatBed();
    void createBlueToy();
    void createKickerToy();
    void createFloor();

    void createPyramid();

private:
    std::shared_ptr<Shader> _basicLitShader;
    std::shared_ptr<Shader> _basicLitTextureShaderGreyFur;
    std::shared_ptr<Shader> _basicLitTextureShaderReddishFluff;
    std::shared_ptr<Shader> _basicLitTextureShaderWoodPlanks;

    std::shared_ptr<Mesh> _cylinder;
    std::shared_ptr<Mesh> _cube;
    std::shared_ptr<Mesh> _pyramid;
    std::shared_ptr<Mesh> _plane;

    std::vector<Model> _models {};
};



