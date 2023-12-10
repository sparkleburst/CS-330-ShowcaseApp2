//
// Created by maxan on 12/3/2023.
//

#include <iostream>
#include "cat_area.h"
#include "texture.h"
#include "shapes.h"
#include "glm/ext/matrix_transform.hpp"

CatArea::CatArea() {
    createShaders();
    createBall1();
    createBall2();
    createBall3();
    createBlueToy();
    createCatBed();
    createKickerToy();
    createPlane();
    createPyramid();
}

void CatArea::Init() {

}

void CatArea::Update(float deltaTime) {
    // could use this for rotation
}

void CatArea::Draw(const SceneParameters& sceneParams) {
    //std::cerr << "Draw" << std::endl;

    Shader* lastBoundShader = nullptr;

    for (auto& model : _models) {
        //std::cerr << "For" << std::endl;
        auto* shader = model.GetShader();
        auto* mesh = model.GetMesh();
        if (!mesh){
            //std::cerr << "Mesh was null" << std::endl;
        }

        if (shader != lastBoundShader) {
            //std::cerr << "if" << std::endl;

            shader->Bind();
            shader->SetMat4("projection", sceneParams.ProjectionMatrix);
            shader->SetMat4("view", sceneParams.ViewMatrix);

            shader->UseTextures(1);

            // handle lights
            //std::cerr << "Handle lights" << std::endl;

            for(auto i = 0; i < sceneParams.Lights.size() && i < MAX_LIGHTS; i++) {
                //std::cerr << "For2" << std::endl;
                std::string uniformName = "lightPos";
                uniformName += std::to_string(i);

                shader->SetVec3(uniformName, sceneParams.Lights[i]);
                //std::cerr << "End of For 2" << std::endl;
            }
        }

        //std::cerr << "set model start" << std::endl;
        shader->SetMat4("model", Transform * mesh->Transform);
        //std::cerr << "about to mesh Draw" << std::endl;
        mesh->Draw();
        //std::cerr << "just did mesh Draw" << std::endl;
    }
    //std::cerr << "End of Draw" << std::endl;
}

void CatArea::ProcessLighting(SceneParameters &sceneParams) {
    // This isn't a light, do nothing
    return;
}

void CatArea::createShaders() {
    _basicLitTextureShaderGreyFur = std::make_shared<Shader>(Path("assets/shaders/basic_lit_texture.vert"),
                                                          Path("assets/shaders/basic_lit_texture.frag"));
    _basicLitTextureShaderReddishFluff = std::make_shared<Shader>(Path("assets/shaders/basic_lit_texture.vert"),
                                                      Path("assets/shaders/basic_lit_texture.frag"));
    _basicLitTextureShaderWoodPlanks = std::make_shared<Shader>(Path("assets/shaders/basic_lit_texture.vert"),
                                                      Path("assets/shaders/basic_lit_texture.frag"));

    auto grey_fur = std::make_shared<Texture>("assets/textures/grey_fur.jpg");
    auto Reddish_Fluff = std::make_shared<Texture>("assets/textures/Reddish_Fluff.png");
    auto wood_planks = std::make_shared<Texture>("assets/textures/wood_planks.jpg");

    _basicLitTextureShaderGreyFur->AddTexture(grey_fur);
    _basicLitTextureShaderReddishFluff->AddTexture(Reddish_Fluff);
    _basicLitTextureShaderWoodPlanks->AddTexture(wood_planks);

    _basicLitShader = std::make_shared<Shader>(Path("assets/shaders/basic_lit.vert"),
                                                   Path("assets/shaders/basic_lit.frag"));
}

void CatArea::createCatBed() {

    // create cat bed
    //auto [cylinderVertices, cylinderElements] = Shapes::BuildCylinderSmooth(32, 1.f, 1.f);
    auto catBedBase = std::make_shared<Mesh>(Shapes::cubeVertices, Shapes::cubeElements,
                                      glm::vec3(0.5f, 0.5f, 0.5f));
    auto bedCylinder1 = std::make_shared<Mesh>(Shapes::someCylinderVertices, Shapes::someCylinderElements,
                                          glm::vec3(0.5f, 0.5f, 0.5f));
    auto bedCylinder2 = std::make_shared<Mesh>(Shapes::someCylinderVertices, Shapes::someCylinderElements,
                                               glm::vec3(0.5f, 0.5f, 0.5f));
    auto bedCylinder3 = std::make_shared<Mesh>(Shapes::someCylinderVertices, Shapes::someCylinderElements,
                                               glm::vec3(0.5f, 0.5f, 0.5f));
    auto bedCylinder4 = std::make_shared<Mesh>(Shapes::someCylinderVertices, Shapes::someCylinderElements,
                                               glm::vec3(0.5f, 0.5f, 0.5f));

    _models.emplace_back(catBedBase, _basicLitTextureShaderGreyFur);
    _models.emplace_back(bedCylinder1, _basicLitTextureShaderGreyFur);
    _models.emplace_back(bedCylinder2, _basicLitTextureShaderGreyFur);
    _models.emplace_back(bedCylinder3, _basicLitTextureShaderGreyFur);
    _models.emplace_back(bedCylinder4, _basicLitTextureShaderGreyFur);

    catBedBase->Transform = glm::translate(catBedBase->Transform, glm::vec3(0.5f, 1.f, 1.f));
    catBedBase->Transform = glm::rotate(catBedBase->Transform, glm::radians(0.f), glm::vec3(1.f, 1.f, 1.f));
    catBedBase->Transform = glm::scale(catBedBase->Transform, glm::vec3(1.f, 0.2f, 1.f));

    bedCylinder1->Transform = glm::translate(bedCylinder1->Transform, glm::vec3(0.f, 0.5f, 0.f));
    bedCylinder2->Transform = glm::translate(bedCylinder2->Transform, glm::vec3(0.5f, 0.f, 0.f));
    bedCylinder3->Transform = glm::translate(bedCylinder3->Transform, glm::vec3(0.f, 0.f, 0.5f));
    bedCylinder4->Transform = glm::translate(bedCylinder4->Transform, glm::vec3(0.5f, 1.f, 1.f));

}

void CatArea::createBall1() {
    auto greenBall = std::make_shared<Mesh>(Shapes::someSphereVertices, Shapes::someSphereIndices,
                                             glm::vec3(0.f, 1.f, 0.f));
    _models.emplace_back(greenBall, _basicLitShader);

}

void CatArea::createBall2() {

}

void CatArea::createBall3() {

}

void CatArea::createBlueToy() {

}

void CatArea::createKickerToy() {

}

void CatArea::createPlane() {
    auto woodFloor = std::make_shared<Mesh>(Shapes::planeVertices, Shapes::planeElements,
                                             glm::vec3(0.5f, 0.5f, 0.5f));

    _models.emplace_back(woodFloor, _basicLitTextureShaderWoodPlanks);
}

void CatArea::createPyramid() {
    /*
    _pyramid = std::make_shared<Mesh>(Shapes::pyramidVertices, Shapes::pyramidElements,
                                               glm::vec3(0.5f, 0.5f, 0.5f));
    if (!_pyramid) {
        std::cerr << "pyramid was null" << std::endl;
    }
    _models.emplace_back(_pyramid, _basicLitTextureShader);
    */
}




