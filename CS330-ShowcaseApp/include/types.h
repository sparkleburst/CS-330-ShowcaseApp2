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

/*
 * to make colors darker change every rgb value by the same percentage eg. for red:
 * {1.0f, 0.0f, 0.0f} becomes {0.8f, 0.0f, 0.0f} each is changed by 20%
 * or more clearly for yellow: {1.0f, 1.0f, 0.5f} becomes {0.8f, 0.8f, 0.4f}
 * */

struct Shapes {
    static inline std::vector<Vertex> cubeVertices {
        // front face
            {
                    .Position = {-0.5f, 0.5f, 0.5f},
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
            {
                    .Position = {0.5f, 0.5f, 0.5f},
                    .Color = {1.0f, 0.0f, 0.0f}
            },
        // right face
            {
                    .Position = {0.5f, 0.5f, 0.5f},
                    .Color = {0.5f, 0.25f, 0.5f} // purple
            },
            {
                    .Position = {0.5f, -0.5f, 0.5f},
                    .Color = {0.5f, 0.25f, 0.5f}
            },
            {
                    .Position = {0.5f, -0.5f, -0.5f},
                    .Color = {0.5f, 0.25f, 0.5f}
            },
            {
                    .Position = {0.5f, 0.5f, -0.5f},
                    .Color = {0.5f, 0.25f, 0.5f}
            },
        // back face
            {
                    .Position = {0.5f, 0.5f, -0.5f},
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
            {
                    .Position = {-0.5f, 0.5f, -0.5f},
                    .Color = {1.0, 0.647, 0.0}
            },
        // left face
            {
                    .Position = {-0.5f, 0.5f, -0.5f},
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
            {
                    .Position = {-0.5f, 0.5f, 0.5f},
                    .Color = {1.0f, 1.0f, 0.5f}
            },
        // top face
            {
                    .Position = {-0.5f, 0.5f, -0.5f},
                    .Color = {0.0f, 1.0f, 0.0f} // green
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
                    .Color = {0.2f, 0.2f, 0.2f} // lighter black (grey)
            },
            {
                    .Position = {0.5f, -0.5f, -0.5f},
                    .Color = {0.0f, 0.0f, 0.0f}
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

