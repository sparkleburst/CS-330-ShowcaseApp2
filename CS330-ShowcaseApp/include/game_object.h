//
// Created by maxan on 12/3/2023.
//

#pragma once
#include <glm/glm.hpp>

class GameObject {
public:
    ~GameObject() = default;
    virtual void Init() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Draw(const glm::mat4& view, const glm::mat4& projection) = 0;

public:
    glm::mat4 Transform {1.f}; //default model matrix
};



