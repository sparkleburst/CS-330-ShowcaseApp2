//
// Created by maxan on 11/7/2023.
//

#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <cmath>
#include <iostream>

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

struct Shapes {
    static inline std::vector<Vertex> planeVertices{
            // a plane is two triangles
            {
                    .Position = {2.5f, -0.1f, 2.5f},
                    .Color = {1.f, 1.f, 1.f}, // white
                    .Uv = {0.f, 1.f}
            },
            {
                    .Position = {2.5f, -0.1f, -2.5f},
                    .Color = {1.f, 1.f, 1.f}, // white
                    .Uv = {0.f, 0.f}
            },
            {
                    .Position = {-2.5f, -0.1f, -2.5f},
                    .Color = {1.f, 1.f, 1.f}, // white
                    .Uv = {1.f, 0.f}
            },
            {
                    .Position = {-2.5f, -0.1f, 2.5f},
                    .Color = {1.f, 1.f, 1.f}, // white
                    .Uv = {1.f, 1.f}
            },
    };

    static inline std::vector<uint32_t> planeElements{
            // indices
            0, 1, 3, 1, 2, 3, // a triangle
    };

    static inline std::vector<Vertex> cubeVertices{
            // front face
            {
                    .Position = {-0.5f, 0.1f, 0.5f},
                    .Color = {0.7f, 0.0f, 0.0f}, // darker red
                    .Uv = {0.f, 4.f}
            },
            {
                    .Position = {-0.5f, -0.1f, 0.5f},
                    .Color = {1.0, 0.0f, 0.0f}, // red
                    .Uv = {0.f, 0.f}
            },
            {
                    .Position = {0.5f, -0.1f, 0.5f},
                    .Color = {1.0f, 0.0f, 0.0f},
                    .Uv = {4.f, 0.f}
            },
            {
                    .Position = {0.5f, 0.1f, 0.5f},
                    .Color = {1.0f, 0.0f, 0.0f},
                    .Uv = {4.f, 4.f}
            },

            // right face
            {
                    .Position = {0.5f, 0.1f, 0.5f},
                    .Color = {0.6f, 0.3f, 0.6f}, // lighter purple
                    .Uv = {0.f, 4.f}
            },
            {
                    .Position = {0.5f, -0.1f, 0.5f},
                    .Color = {0.5f, 0.25f, 0.5f}, // purple
                    .Uv = {0.f, 0.f}
            },
            {
                    .Position = {0.5f, -0.1f, -0.5f},
                    .Color = {0.5f, 0.25f, 0.5f},
                    .Uv = {4.f, 0.f}
            },
            {
                    .Position = {0.5f, 0.1f, -0.5f},
                    .Color = {0.5f, 0.25f, 0.5f},
                    .Uv = {4.f, 4.f}
            },

            // back face
            {
                    .Position = {0.5f, 0.1f, -0.5f},
                    .Color = {0.8, 0.518, 0.0}, // darker orange
                    .Uv = {0.f, 4.f}
            },
            {
                    .Position = {0.5f, -0.1f, -0.5f},
                    .Color = {1.0, 0.647, 0.0}, // orange
                    .Uv = {0.f, 0.f}
            },
            {
                    .Position = {-0.5f, -0.1f, -0.5f},
                    .Color = {1.0, 0.647, 0.0},
                    .Uv = {4.f, 0.f}
            },
            {
                    .Position = {-0.5f, 0.1f, -0.5f},
                    .Color = {1.0, 0.647, 0.0},
                    .Uv = {4.f, 4.f}
            },

            // left face
            {
                    .Position = {-0.5f, 0.1f, -0.5f},
                    .Color = {0.8f, 0.8f, 0.4f}, // darker yellow
                    .Uv = {0.f, 4.f}
            },
            {
                    .Position = {-0.5f, -0.1f, -0.5f}, // yellow
                    .Color = {1.0f, 1.0f, 0.5f},
                    .Uv = {0.f, 0.f}
            },
            {
                    .Position = {-0.5f, -0.1f, 0.5f},
                    .Color = {1.0f, 1.0f, 0.5f},
                    .Uv = {4.f, 0.f}
            },
            {
                    .Position = {-0.5f, 0.1f, 0.5f},
                    .Color = {1.0f, 1.0f, 0.5f},
                    .Uv = {4.f, 4.f}
            },

            // top face
            {
                    .Position = {-0.5f, 0.1f, -0.5f},
                    .Color = {0.6f, 1.0f, 0.6f}, // lighter green
                    .Uv = {0.f, 4.f}
            },
            {
                    .Position = {-0.5f, 0.1f, 0.5f},
                    .Color = {0.0f, 1.0f, 0.0f}, // green
                    .Uv = {0.f, 0.f}
            },
            {
                    .Position = {0.5f, 0.1f, 0.5f},
                    .Color = {0.0f, 1.0f, 0.0f},
                    .Uv = {4.f, 0.f}
            },
            {
                    .Position = {0.5f, 0.1f, -0.5f},
                    .Color = {0.0f, 1.0f, 0.0f},
                    .Uv = {4.f, 4.f}
            },

            // bottom face
            {
                    .Position = {0.5f, -0.1f, 0.5f},
                    .Color = {0.2f, 0.2f, 0.2f}, // lighter black (grey)
                    .Uv = {0.f, 4.f}
            },
            {
                    .Position = {0.5f, -0.1f, -0.5f},
                    .Color = {0.0f, 0.0f, 0.0f}, // black
                    .Uv = {0.f, 0.f}
            },
            {
                    .Position = {-0.5f, -0.1f, -0.5f},
                    .Color = {0.0f, 0.0f, 0.0f},
                    .Uv = {4.f, 0.f}
            },
            {
                    .Position = {-0.5f, -0.1f, 0.5f},
                    .Color = {0.0f, 0.0f, 0.0f},
                    .Uv = {4.f, 4.f}
            }
    };

    static inline std::vector<uint32_t> cubeElements{
            // indices
            0, 1, 3, 1, 2, 3, // front face
            4, 5, 7, 5, 6, 7, // right face
            8, 9, 11, 9, 10, 11, // back face
            12, 13, 15, 13, 14, 15, // left face
            16, 17, 19, 17, 18, 19, // top face
            13, 14, 15, 20, 21, 23, 21, 22, 23 // bottom face
    };

    static inline std::vector<Vertex> pyramidVertices{
            // front face
            { // pyramid tip
                    .Position = {0.f, 0.5f, 0.f},
                    .Color = {1.0, 1.0, 0.8}, // sand
                    .Uv = {1.f, 1.f}
            },
            {
                    .Position = {-0.5f, -0.5f, 0.5f},
                    .Color = {1.0, 1.0, 0.8}, // sand
                    .Uv = {.5f, 0.f}
            },
            {
                    .Position = {0.5f, -0.5f, 0.5f},
                    .Color = {1.0f, 0.0f, 0.0f}, // red
                    .Uv = {1.f, 0.f}
            },

            // right face
            { // pyramid tip
                    .Position = {0.f, 0.5f, 0.f},
                    .Color = {1.0, 1.0, 0.8}, // sand
                    .Uv = {1.f, 1.f}
            },
            {
                    .Position = {0.5f, -0.5f, 0.5f},
                    .Color = {1.0f, 0.0f, 0.0f}, // red
                    .Uv = {.5f, 0.f}
            },
            {
                    .Position = {0.5f, -0.5f, -0.5f},
                    .Color = {1.0, 1.0, 0.8}, // sand
                    .Uv = {1.f, 0.f}
            },

            // back face
            { // pyramid tip
                    .Position = {0.f, 0.5f, 0.f},
                    .Color = {1.0, 1.0, 0.8}, // sand
                    .Uv = {1.f, 1.f}
            },
            {
                    .Position = {0.5f, -0.5f, -0.5f},
                    .Color = {1.0, 1.0, 0.8}, // sand
                    .Uv = {.5f, 0.f}
            },
            {
                    .Position = {-0.5f, -0.5f, -0.5f},
                    .Color = {0.0f, 0.0f, 0.0f}, // black
                    .Uv = {1.f, 0.f}
            },

            // left face
            { // pyramid tip
                    .Position = {0.f, 0.5f, 0.f},
                    .Color = {1.0, 1.0, 0.8}, // sand
                    .Uv = {1.f, 1.f}
            },
            {
                    .Position = {-0.5f, -0.5f, -0.5f},
                    .Color = {0.0f, 0.0f, 0.0f}, // black
                    .Uv = {.5f, 0.f}
            },
            {
                    .Position = {-0.5f, -0.5f, 0.5f},
                    .Color = {1.0, 1.0, 0.8}, // sand
                    .Uv = {1.f, 0.f}
            },

            // bottom face
            {
                    .Position = {0.5f, -0.5f, 0.5f},
                    .Color = {1.0f, 0.0f, 0.0f}, // red
                    .Uv = {0.f, 1.f}
            },
            {
                    .Position = {0.5f, -0.5f, -0.5f},
                    .Color = {1.0, 1.0, 0.8}, // sand
                    .Uv = {0.f, 0.f}
            },
            {
                    .Position = {-0.5f, -0.5f, -0.5f},
                    .Color = {0.0f, 0.0f, 0.0f}, // black
                    .Uv = {1.f, 0.f}
            },
            {
                    {-0.5f, -0.5f, 0.5f},
                    {1.0, 1.0, 0.8}, // sand
                    {0.f, 0.f, 0.f},
                    {1.f, 1.f}
            }
    };


    static inline std::vector<uint32_t> pyramidElements{
            // indices
            0, 1, 2, // front face
            3, 4, 5, // right face
            6, 7, 8, // back face
            9, 10, 11, // left face
            12, 13, 15, 13, 14, 15 // bottom face
    };

    static std::vector<Vertex> getCylinderVertices() {
        std::vector<Vertex> cylinderVertices;

        // Top circle vertices
        cylinderVertices.emplace_back(Vertex{ {0.0f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f},
                                              {0.f, 0.f, 0.f}, {0.5f, 0.5}}); // Top center

        // 15 points around the top circle
        for (int i = 0; i < 15; ++i) {
            float angle = glm::radians(360.0f * static_cast<float>(i) / 15.0f);
            float x = 0.1f * cos(angle);
            float z = 0.1f * sin(angle);

            float u = 0.5f * cos(angle) + 0.5f;
            float v = 0.5f * sin(angle) + 0.5f;

            cylinderVertices.emplace_back(Vertex{ {x, 0.5f, z}, {1.0f, 1.0f, 1.0f},
                                                  {0.f, 0.f, 0.f}, {u, v}});
        }

        // Bottom circle vertices
        cylinderVertices.emplace_back(Vertex{ {0.0f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f},
                                              {0.f, 0.f, 0.f},{0.5f, 0.5f}}); // Bottom center

        // 15 points around the bottom circle
        for (int i = 0; i < 15; ++i) {
            float angle = glm::radians(360.0f * static_cast<float>(i) / 15.0f);
            float x = 0.1f * cos(angle);
            float z = 0.1f * sin(angle);

            float u = 0.5f * cos(angle) + 0.5f;
            float v = 0.5f * sin(angle) + 0.5f;

            cylinderVertices.emplace_back(Vertex{ {x, -0.5f, z}, {1.0f, 1.0f, 1.0f},
                                                  {0.f, 0.f, 0.f}, {u, v}});
        }

        return cylinderVertices;
    }

    static inline std::vector<Vertex> someCylinderVertices = getCylinderVertices();

    static std::vector<uint32_t> getCylinderIndices() {
        std::vector<uint32_t> cylinderIndices;

        // Indices for the top circle
        for (int i = 1; i <= 15; ++i) {
            cylinderIndices.push_back(0);
            cylinderIndices.push_back(i);
            cylinderIndices.push_back((i % 15) + 1);
        }

        // Indices for the bottom circle
        for (int i = 1; i <= 15; ++i) {
            cylinderIndices.push_back(16);
            cylinderIndices.push_back(i + 16);
            cylinderIndices.push_back((i % 15) + 17);
        }

        // Indices for the lateral surface
        for (int i = 1; i <= 15; ++i) {
            int next = (i % 15) + 1;

            cylinderIndices.push_back(i);
            cylinderIndices.push_back(next);
            cylinderIndices.push_back(i + 16);

            cylinderIndices.push_back(next);
            cylinderIndices.push_back(next + 16);
            cylinderIndices.push_back(i + 16);
        }

        return cylinderIndices;
    }

    static inline std::vector<uint32_t> someCylinderElements = getCylinderIndices();

    static std::vector<Vertex> getSphereVertices(float radius, int sectorCount, int stackCount) {
        std::vector<Vertex> sphereVertices;

        float sectorStep = 2 * glm::pi<float>() / sectorCount;
        float stackStep = glm::pi<float>() / stackCount;

        for (int i = 0; i <= stackCount; ++i) {
            float stackAngle = glm::pi<float>() / 2 - i * stackStep;
            float xy = radius * cos(stackAngle);
            float z = radius * sin(stackAngle);

            for (int j = 0; j <= sectorCount; ++j) {
                float sectorAngle = j * sectorStep;

                float x = xy * cos(sectorAngle);
                float y = xy * sin(sectorAngle);

                glm::vec3 position(x, y, z);
                glm::vec3 normal = glm::normalize(position);
                glm::vec2 uv(static_cast<float>(j) / sectorCount, static_cast<float>(i) / stackCount);

                sphereVertices.emplace_back(Vertex{position, {1.0f, 1.0f, 1.0f}, normal, uv});
            }
        }

        return sphereVertices;
    }

    static std::vector<uint32_t> getSphereIndices(int sectorCount, int stackCount) {
        std::vector<uint32_t> sphereIndices;

        for (int i = 0; i < stackCount; ++i) {
            for (int j = 0; j < sectorCount; ++j) {
                int k0 = i * (sectorCount + 1) + j;
                int k1 = k0 + 1;
                int k2 = k0 + sectorCount + 1;
                int k3 = k2 + 1;

                sphereIndices.push_back(k0);
                sphereIndices.push_back(k2);
                sphereIndices.push_back(k1);

                sphereIndices.push_back(k1);
                sphereIndices.push_back(k2);
                sphereIndices.push_back(k3);
            }
        }

        return sphereIndices;
    }

    static inline std::vector<Vertex> someSphereVertices = getSphereVertices(0.5f, 20, 20);
    static inline std::vector<uint32_t> someSphereIndices = getSphereIndices(20, 20);
};