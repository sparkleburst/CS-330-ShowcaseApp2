//
// Created by maxan on 11/7/2023.
//

#pragma once
#include <glm/glm.hpp>
#include <vector>

constexpr uint8_t MAX_LIGHTS = 2;

// each triangle will have some or all of the attributes below
struct Vertex {
    glm::vec3 Position {0.f, 0.f, 0.f}; // default position of (0,0,0)
    glm::vec3 Color {1.f, 1.f, 1.f}; // default color white
    glm::vec3 Normal {0.f, 0.f, 0.f};
    glm::vec2 Uv {1.f, 1.f};
};

/*
 * to make colors darker change every rgb value by the same percentage eg. for red:
 * {1.0f, 0.0f, 0.0f} becomes {0.8f, 0.0f, 0.0f} each is changed by 20%
 * or more clearly for yellow: {1.0f, 1.0f, 0.5f} becomes {0.8f, 0.8f, 0.4f}
 */

/*
 * a Uv greater than 1 will make tiles. for example change all 1's, (0.f, 5.f) (5.f, 0.f)
 * a Uv smaller than 1 will stretch the Uv
 */

struct SceneParameters{
    glm::mat4 ProjectionMatrix { 1.f };
    glm::mat4 ViewMatrix { 1.f };

    std::vector<glm::vec3> Lights {};
};