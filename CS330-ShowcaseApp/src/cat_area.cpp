//
// Created by maxan on 12/3/2023.
//

#include "cat_area.h"
#include "texture.h"
#include "types.h"

CatArea::CatArea() {
    createShaders();
    createBall1();
    createBall2();
    createBall3();
    createBlueToy();
    createCatBed();
    createKickerToy();
    createPyramid();
}

void CatArea::Init() {

}

void CatArea::Update(float deltaTime) {
    // could use this for rotation
}

void CatArea::Draw(const glm::mat4 &view, const glm::mat4 &projection) {
    for (auto& model : _models) {
        auto *shader = model.GetShader();
        auto *mesh = model.GetMesh();
        shader->Bind();
        shader->SetMat4("projection", projection);
        shader->SetMat4("view", view);
        shader->SetMat4("model", Transform * mesh->Transform);

        mesh->Draw();
    }
}

void CatArea::createShaders() {
        _textureShader = std::make_shared<Shader>(Path("basic_unlit_color.vert"), Path("basic_unlit_color.frag"));
        auto catBedTexture1 = std::make_shared<Texture>("grey_fur.jpg");
        auto catBedTexture2 = std::make_shared<Texture>("Reddish_Fluff.png");

        //_textureShader->AddTexture(catBedTexture1);
        //_textureShader->AddTexture(catBedTexture2);

        _basicLitShader = std::make_shared<Shader>(Path("basic_lit.vert"),
                                                   Path("basic_lit.frag"));
}



void CatArea::createCatBed() {
    // create cat bed
    //auto [cylinderVertices, cylinderElements] = Shapes::BuildCylinderSmooth(32, 1.f, 1.f);
    auto bedCube = std::make_shared<Mesh>(Shapes::cubeVertices, Shapes::cubeElements,
                                          glm::vec3(0.5f, 0.5f, 0.5f));
    auto bedCylinder1 = std::make_shared<Mesh>(Shapes::cubeVertices, Shapes::cubeElements,
                                          glm::vec3(0.5f, 0.5f, 0.5f));
    auto bedCylinder2 = std::make_shared<Mesh>(Shapes::cubeVertices, Shapes::cubeElements,
                                               glm::vec3(0.5f, 0.5f, 0.5f));
    auto bedCylinder3 = std::make_shared<Mesh>(Shapes::cubeVertices, Shapes::cubeElements,
                                               glm::vec3(0.5f, 0.5f, 0.5f));
    auto bedCylinder4 = std::make_shared<Mesh>(Shapes::cubeVertices, Shapes::cubeElements,
                                               glm::vec3(0.5f, 0.5f, 0.5f));

}

void CatArea::createBall1() {

}

void CatArea::createBall2() {

}

void CatArea::createBall3() {

}

void CatArea::createBlueToy() {

}

void CatArea::createKickerToy() {

}

void CatArea::createPyramid() {
    auto bedCylinder1 = std::make_shared<Mesh>(Shapes::cubeVertices, Shapes::cubeElements,
                                               glm::vec3(0.5f, 0.5f, 0.5f));
    _models.emplace_back(_pyramid, _basicLitShader);

}
