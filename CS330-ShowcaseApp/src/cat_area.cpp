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
    auto bedCorner1 = std::make_shared<Mesh>(Shapes::someSphereVertices, Shapes::someSphereIndices,
                                             glm::vec3(0.5f, 0.5f, 0.5f));
    auto bedCorner2 = std::make_shared<Mesh>(Shapes::someSphereVertices, Shapes::someSphereIndices,
                                             glm::vec3(0.5f, 0.5f, 0.5f));
    auto bedCorner3 = std::make_shared<Mesh>(Shapes::someSphereVertices, Shapes::someSphereIndices,
                                             glm::vec3(0.5f, 0.5f, 0.5f));
    auto bedCorner4 = std::make_shared<Mesh>(Shapes::someSphereVertices, Shapes::someSphereIndices,
                                             glm::vec3(0.5f, 0.5f, 0.5f));

    // textures for cat bed
    _models.emplace_back(catBedBase, _basicLitTextureShaderGreyFur);
    _models.emplace_back(bedCylinder1, _basicLitTextureShaderGreyFur);
    _models.emplace_back(bedCylinder2, _basicLitTextureShaderGreyFur);
    _models.emplace_back(bedCylinder3, _basicLitTextureShaderGreyFur);
    _models.emplace_back(bedCylinder4, _basicLitTextureShaderGreyFur);
    _models.emplace_back(bedCorner1, _basicLitTextureShaderGreyFur);
    _models.emplace_back(bedCorner2, _basicLitTextureShaderGreyFur);
    _models.emplace_back(bedCorner3, _basicLitTextureShaderGreyFur);
    _models.emplace_back(bedCorner4, _basicLitTextureShaderGreyFur);

    // translate = move object, rotate = turn object, scale is make object correct size
    catBedBase->Transform = glm::translate(catBedBase->Transform, glm::vec3(0.0f, 0.05f, -0.8f));
    catBedBase->Transform = glm::scale(catBedBase->Transform, glm::vec3(0.6f, 0.1f, 0.5f));

    bedCylinder1->Transform = glm::translate(bedCylinder1->Transform, glm::vec3(-0.55f, 0.23f, -0.8f)); // left
    bedCylinder1->Transform = glm::rotate(bedCylinder1->Transform, glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f));

    bedCylinder2->Transform = glm::translate(bedCylinder2->Transform, glm::vec3(0.55f, 0.23f, -0.8f)); // right
    bedCylinder2->Transform = glm::rotate(bedCylinder2->Transform, glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f));

    bedCylinder3->Transform = glm::translate(bedCylinder3->Transform, glm::vec3(0.0f, 0.23f, -1.25f)); // back
    bedCylinder3->Transform = glm::rotate(bedCylinder3->Transform, glm::radians(90.f), glm::vec3(0.f, 0.f, 1.f));
    bedCylinder3->Transform = glm::scale(bedCylinder3->Transform, glm::vec3(1.f, 1.2f, 1.f));

    bedCylinder4->Transform = glm::translate(bedCylinder4->Transform, glm::vec3(0.0f, 0.2f, -0.35f)); // front
    bedCylinder4->Transform = glm::rotate(bedCylinder4->Transform, glm::radians(90.f), glm::vec3(0.f, 0.f, 1.f));
    bedCylinder4->Transform = glm::scale(bedCylinder4->Transform, glm::vec3(1.f, 1.2f, 1.f));

    bedCorner1->Transform = glm::translate(bedCorner1->Transform, glm::vec3(-0.54f, 0.23f, -1.24f)); // back left
    bedCorner1->Transform = glm::scale(bedCorner1->Transform, glm::vec3(0.245f, 0.245f, 0.245f));

    bedCorner2->Transform = glm::translate(bedCorner2->Transform, glm::vec3(0.54f, 0.23f, -1.24f)); // back right
    bedCorner2->Transform = glm::scale(bedCorner2->Transform, glm::vec3(0.245f, 0.245f, 0.245f));

    bedCorner3->Transform = glm::translate(bedCorner3->Transform, glm::vec3(-0.54f, 0.22f, -0.34f)); // front left
    bedCorner3->Transform = glm::scale(bedCorner3->Transform, glm::vec3(0.245f, 0.245f, 0.245f));

    bedCorner4->Transform = glm::translate(bedCorner4->Transform, glm::vec3(0.54f, 0.22f, -0.34f)); // front right
    bedCorner4->Transform = glm::scale(bedCorner4->Transform, glm::vec3(0.245f, 0.245f, 0.245f));
}

void CatArea::createBlueToy() {

    // make balls
    auto greenBall = std::make_shared<Mesh>(Shapes::someSphereVertices, Shapes::someSphereIndices,
                                            glm::vec3(0.f, 1.f, 0.f));
    auto redBall = std::make_shared<Mesh>(Shapes::someSphereVertices, Shapes::someSphereIndices,
                                          glm::vec3(1.f, 0.f, 0.f));
    auto yellowBall = std::make_shared<Mesh>(Shapes::someSphereVertices, Shapes::someSphereIndices,
                                             glm::vec3(1.f, 1.f, 0.f));

    _models.emplace_back(greenBall, _basicLitShader);
    _models.emplace_back(redBall, _basicLitShader);
    _models.emplace_back(yellowBall, _basicLitShader);

    greenBall->Transform = glm::translate(greenBall->Transform, glm::vec3(-0.5f, 0.01f, 0.72f));
    greenBall->Transform = glm::scale(greenBall->Transform, glm::vec3(0.125f, 0.125f, 0.125f));

    redBall->Transform = glm::translate(redBall->Transform, glm::vec3(0.f, 0.01f, 0.f));
    redBall->Transform = glm::scale(redBall->Transform, glm::vec3(0.125f, 0.125f, 0.125f));

    yellowBall->Transform = glm::translate(yellowBall->Transform, glm::vec3(-0.36f, 0.26f, 0.45f));
    yellowBall->Transform = glm::scale(yellowBall->Transform, glm::vec3(0.125f, 0.125f, 0.125f));

    // make blue cylinder
    auto blueCylinder = std::make_shared<Mesh>(Shapes::someCylinderVertices, Shapes::someCylinderElements,
                                                 glm::vec3(0.f, 0.f, 1.f));

    _models.emplace_back(blueCylinder, _basicLitShader);

    blueCylinder->Transform = glm::translate(blueCylinder->Transform, glm::vec3(-0.5f, 0.14f, 0.5f));
    blueCylinder->Transform = glm::scale(blueCylinder->Transform, glm::vec3(0.7f, 0.38f, 0.7f));

    // make blue circles
    auto blueCircleBig1 = std::make_shared<Mesh>(Shapes::someCircleVertices, Shapes::someCircleElements,
                                            glm::vec3(0.f, 0.f, 1.f));
    auto blueCircleBig2 = std::make_shared<Mesh>(Shapes::someCircleVertices, Shapes::someCircleElements,
                                                 glm::vec3(0.f, 0.f, 1.f));
    auto blueCircleMedium = std::make_shared<Mesh>(Shapes::someCircleVertices, Shapes::someCircleElements,
                                                 glm::vec3(0.f, 0.f, 1.f));
    auto blueCircleSmall = std::make_shared<Mesh>(Shapes::someCircleVertices, Shapes::someCircleElements,
                                                 glm::vec3(0.f, 0.f, 1.f));

    _models.emplace_back(blueCircleBig1, _basicLitShader);
    _models.emplace_back(blueCircleBig2, _basicLitShader);
    _models.emplace_back(blueCircleMedium, _basicLitShader);
    _models.emplace_back(blueCircleSmall, _basicLitShader);

    blueCircleBig1->Transform = glm::translate(blueCircleBig1->Transform, glm::vec3(-0.5f, -0.55f, 0.5f));
    blueCircleBig1->Transform = glm::scale(blueCircleBig1->Transform, glm::vec3(3.2f, 1.0f, 3.2f));

    blueCircleBig2->Transform = glm::translate(blueCircleBig2->Transform, glm::vec3(-0.5f, -0.425f, 0.5f));
    blueCircleBig2->Transform = glm::scale(blueCircleBig2->Transform, glm::vec3(3.0f, 1.0f, 3.0f));

    blueCircleMedium->Transform = glm::translate(blueCircleMedium->Transform, glm::vec3(-0.5f, -0.3f, 0.5f));
    blueCircleMedium->Transform = glm::scale(blueCircleMedium->Transform, glm::vec3(2.5f, 1.0f, 2.5f));

    blueCircleSmall->Transform = glm::translate(blueCircleSmall->Transform, glm::vec3(-0.5f, -0.175f, 0.5f));
    blueCircleSmall->Transform = glm::scale(blueCircleSmall->Transform, glm::vec3(2.0f, 1.0f, 2.0f));
}

void CatArea::createKickerToy() {

    // make long cone
    auto longCone = std::make_shared<Mesh>(Shapes::someConeVertices, Shapes::someConeElements,
                                           glm::vec3(1.f, 0.647f, 0.f));

    _models.emplace_back(longCone, _basicLitTextureShaderReddishFluff);

    longCone->Transform = glm::translate(longCone->Transform, glm::vec3(0.875f, 0.0195f, 0.158f));
    longCone->Transform = glm::rotate(longCone->Transform, glm::radians(205.f), glm::vec3(1.f, 1.1f, 0.f));
    longCone->Transform = glm::scale(longCone->Transform, glm::vec3(1.f, 0.7f, 1.f));

    // put ball on top
    auto kickerTop = std::make_shared<Mesh>(Shapes::someSphereVertices, Shapes::someSphereIndices,
                                            glm::vec3(0.f, 1.f, 0.f));

    _models.emplace_back(kickerTop, _basicLitTextureShaderReddishFluff);

    kickerTop->Transform = glm::translate(kickerTop->Transform, glm::vec3(1.2f, 0.065f, 0.06f));
    kickerTop->Transform = glm::scale(kickerTop->Transform, glm::vec3(0.197f, 0.197f, 0.197f));

    // put second squished cone on top again
    auto squishedCone = std::make_shared<Mesh>(Shapes::someConeVertices, Shapes::someConeElements,
                                           glm::vec3(1.f, 0.647f, 0.f));

    _models.emplace_back(squishedCone, _basicLitTextureShaderReddishFluff);

    squishedCone->Transform = glm::translate(squishedCone->Transform, glm::vec3(1.2f, 0.07f, 0.06f));
    squishedCone->Transform = glm::rotate(squishedCone->Transform, glm::radians(205.f), glm::vec3(1.f, 1.1f, 0.f));
    squishedCone->Transform = glm::scale(squishedCone->Transform, glm::vec3(0.9f, 0.3f, 0.9f));

    // put planes at very top as strings
    auto kickerString1 = std::make_shared<Mesh>(Shapes::planeVertices, Shapes::planeElements,
                                            glm::vec3(0.5f, 1.0f, 0.5f));

    _models.emplace_back(kickerString1, _basicLitShader);

    kickerString1->Transform = glm::translate(kickerString1->Transform, glm::vec3(1.35f, 0.09f, 0.f));
    kickerString1->Transform = glm::rotate(kickerString1->Transform, glm::radians(105.f), glm::vec3(0.0f, 1.f, 0.f));
    kickerString1->Transform = glm::scale(kickerString1->Transform, glm::vec3(0.005f, 1.f, 0.05f));

    auto kickerString2 = std::make_shared<Mesh>(Shapes::planeVertices, Shapes::planeElements,
                                                glm::vec3(0.5f, 1.0f, 0.5f));

    _models.emplace_back(kickerString2, _basicLitShader);

    kickerString2->Transform = glm::translate(kickerString2->Transform, glm::vec3(1.35f, 0.09f, 0.f));
    kickerString2->Transform = glm::rotate(kickerString2->Transform, glm::radians(105.f), glm::vec3(0.3f, 1.f, 0.f));
    kickerString2->Transform = glm::scale(kickerString2->Transform, glm::vec3(0.005f, 1.f, 0.05f));

    auto kickerString3 = std::make_shared<Mesh>(Shapes::planeVertices, Shapes::planeElements,
                                                glm::vec3(0.5f, 1.0f, 0.5f));

    _models.emplace_back(kickerString3, _basicLitShader);

    kickerString3->Transform = glm::translate(kickerString3->Transform, glm::vec3(1.35f, 0.09f, 0.f));
    kickerString3->Transform = glm::rotate(kickerString3->Transform, glm::radians(105.f), glm::vec3(0.0f, 1.f, 0.5f));
    kickerString3->Transform = glm::scale(kickerString3->Transform, glm::vec3(0.005f, 1.f, 0.05f));
}

void CatArea::createFloor() {
    auto woodFloor = std::make_shared<Mesh>(Shapes::planeVertices, Shapes::planeElements,
                                             glm::vec3(0.5f, 0.5f, 0.5f));

    _models.emplace_back(woodFloor, _basicLitTextureShaderWoodPlanks);

    woodFloor->Transform = glm::translate(woodFloor->Transform, glm::vec3(0.f, -0.051f, -0.4f));
    woodFloor->Transform = glm::scale(woodFloor->Transform, glm::vec3(0.75f, 1.f, 0.75f));

    auto woodFloorUnder = std::make_shared<Mesh>(Shapes::planeVertices, Shapes::planeElements,
                                            glm::vec3(0.5f, 0.5f, 0.5f));

    _models.emplace_back(woodFloorUnder, _basicLitTextureShaderWoodPlanks);

    woodFloorUnder->Transform = glm::translate(woodFloorUnder->Transform, glm::vec3(0.f, -0.051f, -0.4f));
    woodFloorUnder->Transform = glm::rotate(woodFloorUnder->Transform, glm::radians(180.f), glm::vec3(1.0f, 0.0f, 1.0f));
    woodFloorUnder->Transform = glm::scale(woodFloorUnder->Transform, glm::vec3(0.75f, 1.f, 0.75f));
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




