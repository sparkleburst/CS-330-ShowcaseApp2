//
// Created by maxan on 11/7/2023.
//

#pragma once
#include <glm/glm.hpp>

// each triangle will have some or all of the attributes below
struct Vertex {
    glm::vec3 Position {0.f, 0.f, 0.f}; // default position of (0,0,0)
    glm::vec3 Color {1.f, 1.f, 1.f}; // default color white
    glm::vec3 Normal {0.f, 0.f, 0.f};
    glm::vec2 Uv {1.f, 1.f};
};

struct Shapes {
    static inline std::vector<Vertex> cubeVertices {
        // front face
            {
                    .Position = {-0.5f, 0.5f, 0.5f},
                    .Color = {1.0f, 0.5f, 0.5f} // red
            },
            {
                    .Position = {-0.5f, -0.5f, 0.5f},
                    .Color = {1.0f, 0.5f, 0.5f}
            },
            {
                    .Position = {0.5f, -0.5f, 0.5f},
                    .Color = {1.0f, 0.5f, 0.5f}
            },
            {
                    .Position = {0.5f, 0.5f, 0.5f},
                    .Color = {1.0f, 0.5f, 0.5f}
            },
        // right face
            {
                    .Position = {0.5f, 0.5f, 0.5f},
                    .Color = {0.5f, 0.5f, 0.5f}
            },
            {
                    .Position = {0.5f, -0.5f, 0.5f},
                    .Color = {0.5f, 0.5f, 0.5f}
            },
            {
                    .Position = {0.5f, -0.5f, -0.5f},
                    .Color = {0.5f, 0.5f, 0.5f}
            },
            {
                    .Position = {0.5f, 0.5f, -0.5f},
                    .Color = {0.5f, 0.5f, 0.5f}
            },
        // back face
            {
                    .Position = {0.5f, 0.5f, -0.5f},
                    .Color = {1.0f, 1.0f, 0.5f}
            },
            {
                    .Position = {0.5f, -0.5f, -0.5f},
                    .Color = {1.0f, 1.0f, 0.5f}
            },
            {
                    .Position = {-0.5f, -0.5f, -0.5f},
                    .Color = {1.0f, 1.0f, 0.5f}
            },
            {
                    .Position = {-0.5f, 0.5f, -0.5f},
                    .Color = {1.0f, 1.0f, 0.5f}
            },
        // left face
            {
                    .Position = {-0.5f, 0.5f, -0.5f},
                    .Color = {0.0f, 0.5f, 0.0f}
            },
            {
                    .Position = {-0.5f, -0.5f, -0.5f},
                    .Color = {0.0f, 0.5f, 0.0f}
            },
            {
                    .Position = {-0.5f, -0.5f, 0.5f},
                    .Color = {0.0f, 0.5f, 0.0f}
            },
            {
                    .Position = {-0.5f, 0.5f, 0.5f},
                    .Color = {0.0f, 0.5f, 0.0f}
            },
        // top face
            {
                    .Position = {-0.5f, 0.5f, -0.5f},
                    .Color = {0.0f, 1.0f, 0.0f}
            },
            {
                    .Position = {-0.5f, 0.5f, 0.5f},
                    .Color = {0.0f, 1.0f, 0.0f}
            },
            {
                    .Position = {0.5f, 0.5f, 0.5f},
                    .Color = {0.0f, 1.0f, 0.0f}
            },
            {
                    .Position = {0.5f, 0.5f, -0.5f},
                    .Color = {0.0f, 1.0f, 0.0f}
            },
        // bottom face
            {
                    .Position = {0.5f, -0.5f, 0.5f},
                    .Color = {0.0f, 0.5f, 0.0f}
            },
            {
                    .Position = {0.5f, -0.5f, -0.5f},
                    .Color = {0.0f, 0.5f, 0.0f}
            },
            {
                    .Position = {-0.5f, -0.5f, -0.5f},
                    .Color = {0.0f, 0.5f, 0.0f}
            },
            {
                    .Position = {-0.5f, -0.5f, 0.5f},
                    .Color = {0.0f, 0.5f, 0.0f}
            }
    };


    static inline std::vector<uint32_t> cubeElements {
        // indices
        0, 1, 3, 1, 2, 3, // front face
        4, 5, 7, 5, 6, 7, // right face
        8, 9, 11, 9, 10, 11, // back face
        12, 13, 15, 13, 14, 15, // left face
        16, 17, 19, 17, 18, 19, // top face
        20, 21, 23, 21, 22, 23 // bottom face
    };
};

