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
    createCatBed();
    createBlueToy();
    createKickerToy();
    createFloor();
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

            // set camera position
            shader->SetVec3("eyePos", sceneParams.CameraPosition);

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

    // textures for cat bed
    _models.emplace_back(catBedBase, _basicLitTextureShaderGreyFur);
    _models.emplace_back(bedCylinder1, _basicLitTextureShaderGreyFur);
    _models.emplace_back(bedCylinder2, _basicLitTextureShaderGreyFur);
    _models.emplace_back(bedCylinder3, _basicLitTextureShaderGreyFur);
    _models.emplace_back(bedCylinder4, _basicLitTextureShaderGreyFur);

    // translate = move object, rotate = turn object, scale is make object correct size
    catBedBase->Transform = glm::translate(catBedBase->Transform, glm::vec3(0.5f, 1.f, 1.f));
    catBedBase->Transform = glm::scale(catBedBase->Transform, glm::vec3(1.f, 0.2f, 1.f));

    bedCylinder1->Transform = glm::translate(bedCylinder1->Transform, glm::vec3(0.f, 0.5f, 0.f));
    bedCylinder1->Transform = glm::rotate(bedCylinder1->Transform, glm::radians(0.f), glm::vec3(1.f, 1.f, 1.f));

    bedCylinder2->Transform = glm::translate(bedCylinder2->Transform, glm::vec3(0.5f, 0.f, 0.f));
    bedCylinder2->Transform = glm::rotate(bedCylinder2->Transform, glm::radians(0.f), glm::vec3(1.f, 1.f, 1.f));

    bedCylinder3->Transform = glm::translate(bedCylinder3->Transform, glm::vec3(0.f, 0.f, 0.5f));
    bedCylinder3->Transform = glm::rotate(bedCylinder3->Transform, glm::radians(0.f), glm::vec3(1.f, 1.f, 1.f));

    bedCylinder4->Transform = glm::translate(bedCylinder4->Transform, glm::vec3(0.5f, 1.f, 1.f));
    bedCylinder4->Transform = glm::rotate(bedCylinder4->Transform, glm::radians(0.f), glm::vec3(1.f, 1.f, 1.f));

}


void CatArea::createBlueToy() {

    auto greenBall = std::make_shared<Mesh>(Shapes::someSphereVertices, Shapes::someSphereIndices,
                                            glm::vec3(0.f, 1.f, 0.f));
    auto redBall = std::make_shared<Mesh>(Shapes::someSphereVertices, Shapes::someSphereIndices,
                                          glm::vec3(1.f, 0.f, 0.f));
    auto yellowBall = std::make_shared<Mesh>(Shapes::someSphereVertices, Shapes::someSphereIndices,
                                             glm::vec3(1.f, 1.f, 0.f));

    _models.emplace_back(greenBall, _basicLitShader);
    _models.emplace_back(redBall, _basicLitShader);
    _models.emplace_back(yellowBall, _basicLitShader);

    greenBall->Transform = glm::translate(greenBall->Transform, glm::vec3(-0.5f, 1.f, 1.f));
    greenBall->Transform = glm::scale(greenBall->Transform, glm::vec3(0.1f, 0.1f, 0.1));

    redBall->Transform = glm::translate(redBall->Transform, glm::vec3(-1.f, 1.f, 1.f));
    redBall->Transform = glm::scale(redBall->Transform, glm::vec3(0.1f, 0.1f, 0.1));

    yellowBall->Transform = glm::translate(yellowBall->Transform, glm::vec3(-1.5f, 1.f, 1.f));
    yellowBall->Transform = glm::scale(yellowBall->Transform, glm::vec3(0.1f, 0.1f, 0.1));

    // make blue cylinder
    // make blue circles
    // move balls to correct spots

}

void CatArea::createKickerToy() {

    // make long cone
    // put ball on top
    // put second squished cone on top again
    // put cylinders at very top as strings

}

void CatArea::createFloor() {
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




