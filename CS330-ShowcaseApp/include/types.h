//
// Created by maxan on 11/7/2023.
//

#pragma once
#include <glm/glm.hpp>
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

struct Shapes {
    static inline std::vector<Vertex> planeVertices{
            // a plane is two triangles
            {
                    .Position = {2.5f, -0.1f, 2.5f},
                    .Color = {0.0, 0.3f, 0.0f} // darker green
            },
            {
                    .Position = {2.5f, -0.1f, -2.5f},
                    .Color = {0.0, 0.3f, 0.0f} // darker green
            },
            {
                    .Position = {-2.5f, -0.1f, -2.5f},
                    .Color = {0.0, 0.3f, 0.0f} // darker green
            },
            {
                    .Position = {-2.5f, -0.1f, 2.5f},
                    .Color = {0.0, 0.3f, 0.0f} // darker green
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
                    .Color = {0.7f, 0.0f, 0.0f} // darker red
            },
            {
                    .Position = {-0.5f, -0.1f, 0.5f},
                    .Color = {1.0, 0.0f, 0.0f} // red
            },
            {
                    .Position = {0.5f, -0.1f, 0.5f},
                    .Color = {1.0f, 0.0f, 0.0f}
            },
            {
                    .Position = {0.5f, 0.1f, 0.5f},
                    .Color = {1.0f, 0.0f, 0.0f}
            },

            // right face
            {
                    .Position = {0.5f, 0.1f, 0.5f},
                    .Color = {0.6f, 0.3f, 0.6f} // lighter purple
            },
            {
                    .Position = {0.5f, -0.1f, 0.5f},
                    .Color = {0.5f, 0.25f, 0.5f} // purple
            },
            {
                    .Position = {0.5f, -0.1f, -0.5f},
                    .Color = {0.5f, 0.25f, 0.5f}
            },
            {
                    .Position = {0.5f, 0.1f, -0.5f},
                    .Color = {0.5f, 0.25f, 0.5f}
            },

            // back face
            {
                    .Position = {0.5f, 0.1f, -0.5f},
                    .Color = {0.8, 0.518, 0.0} // darker orange
            },
            {
                    .Position = {0.5f, -0.1f, -0.5f},
                    .Color = {1.0, 0.647, 0.0} // orange
            },
            {
                    .Position = {-0.5f, -0.1f, -0.5f},
                    .Color = {1.0, 0.647, 0.0}
            },
            {
                    .Position = {-0.5f, 0.1f, -0.5f},
                    .Color = {1.0, 0.647, 0.0}
            },

            // left face
            {
                    .Position = {-0.5f, 0.1f, -0.5f},
                    .Color = {0.8f, 0.8f, 0.4f} // darker yellow
            },
            {
                    .Position = {-0.5f, -0.1f, -0.5f}, // yellow
                    .Color = {1.0f, 1.0f, 0.5f}
            },
            {
                    .Position = {-0.5f, -0.1f, 0.5f},
                    .Color = {1.0f, 1.0f, 0.5f}
            },
            {
                    .Position = {-0.5f, 0.1f, 0.5f},
                    .Color = {1.0f, 1.0f, 0.5f}
            },

            // top face
            {
                    .Position = {-0.5f, 0.1f, -0.5f},
                    .Color = {0.6f, 1.0f, 0.6f} // lighter green
            },
            {
                    .Position = {-0.5f, 0.1f, 0.5f},
                    .Color = {0.0f, 1.0f, 0.0f} // green
            },
            {
                    .Position = {0.5f, 0.1f, 0.5f},
                    .Color = {0.0f, 1.0f, 0.0f}
            },
            {
                    .Position = {0.5f, 0.1f, -0.5f},
                    .Color = {0.0f, 1.0f, 0.0f}
            },

            // bottom face
            {
                    .Position = {0.5f, -0.1f, 0.5f},
                    .Color = {0.2f, 0.2f, 0.2f} // lighter black (grey)
            },
            {
                    .Position = {0.5f, -0.1f, -0.5f},
                    .Color = {0.0f, 0.0f, 0.0f} // black
            },
            {
                    .Position = {-0.5f, -0.1f, -0.5f},
                    .Color = {0.0f, 0.0f, 0.0f}
            },
            {
                    .Position = {-0.5f, -0.1f, 0.5f},
                    .Color = {0.0f, 0.0f, 0.0f}
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
                    .Color = {0.8f, 0.0f, 0.0f} // darker red
            },
            {
                    .Position = {-0.5f, -0.5f, 0.5f},
                    .Color = {1.0f, 0.0f, 0.0f} // red
            },
            {
                    .Position = {0.5f, -0.5f, 0.5f},
                    .Color = {1.0f, 0.0f, 0.0f}
            },

            // right face
            { // pyramid tip
                    .Position = {0.f, 0.5f, 0.f},
                    .Color = {0.6f, 0.3f, 0.6f} // lighter purple
            },
            {
                    .Position = {0.5f, -0.5f, 0.5f},
                    .Color = {0.5f, 0.25f, 0.5f} // purple
            },
            {
                    .Position = {0.5f, -0.5f, -0.5f},
                    .Color = {0.5f, 0.25f, 0.5f}
            },

            // back face
            { // pyramid tip
                    .Position = {0.f, 0.5f, 0.f},
                    .Color = {0.8, 0.518, 0.0} // darker orange
            },
            {
                    .Position = {0.5f, -0.5f, -0.5f},
                    .Color = {1.0, 0.647, 0.0} // orange
            },
            {
                    .Position = {-0.5f, -0.5f, -0.5f},
                    .Color = {1.0, 0.647, 0.0}
            },

            // left face
            { // pyramid tip
                    .Position = {0.f, 0.5f, 0.f},
                    .Color = {0.8f, 0.8f, 0.4f} // darker yellow
            },
            {
                    .Position = {-0.5f, -0.5f, -0.5f}, // yellow
                    .Color = {1.0f, 1.0f, 0.5f}
            },
            {
                    .Position = {-0.5f, -0.5f, 0.5f},
                    .Color = {1.0f, 1.0f, 0.5f}
            },

            // bottom face
            {
                    .Position = {0.5f, -0.5f, 0.5f},
                    .Color = {0.2f, 0.2f, 0.2f} // lighter black (grey)
            },
            {
                    .Position = {0.5f, -0.5f, -0.5f},
                    .Color = {0.0f, 0.0f, 0.0f} // black
            },
            {
                    .Position = {-0.5f, -0.5f, -0.5f},
                    .Color = {0.0f, 0.0f, 0.0f}
            },
            {
                    .Position = {-0.5f, -0.5f, 0.5f},
                    .Color = {0.0f, 0.0f, 0.0f}
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
        cylinderVertices.emplace_back(Vertex{ {0.0f, 0.1f, 0.0f}, {1.0f, 0.0f, 0.0f}}); // Top center

        // 15 points around the top circle
        for (int i = 0; i < 15; ++i) {
            float angle = glm::radians(360.0f * static_cast<float>(i) / 15.0f);
            float x = 0.1f * cos(angle);
            float z = 0.1f * sin(angle);

            cylinderVertices.emplace_back(Vertex{ {x, 0.5f, z}, {1.0f, 0.0f, 0.0f} });
        }

        // Bottom circle vertices
        cylinderVertices.emplace_back(Vertex{ {0.0f, -0.1f, 0.0f}, {0.0f, 0.0f, 1.0f}}); // Bottom center

        // 15 points around the bottom circle
        for (int i = 0; i < 15; ++i) {
            float angle = glm::radians(360.0f * static_cast<float>(i) / 15.0f);
            float x = 0.1f * cos(angle);
            float z = 0.1f * sin(angle);

            cylinderVertices.emplace_back(Vertex{ {x, -0.5f, z}, {0.0f, 0.0f, 1.0f} });
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
        for (int i = 17; i <= 31; ++i) {
            cylinderIndices.push_back(16);
            cylinderIndices.push_back(i);
            cylinderIndices.push_back((i % 31) + 17);
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
};