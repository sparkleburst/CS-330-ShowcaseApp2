//
// Created by maxan on 12/5/2023.
//

#pragma once

#include <types.h>

#include <glm/glm.hpp>
#include <vector>

#include <numbers>
#include <tuple>
#include <vector>

struct Shapes {
    static inline void UpdateNormals(Vertex& p1, Vertex& p2, Vertex& p3) {
        glm::vec3 U = p2.Position - p1.Position;
        glm::vec3 V = p3.Position - p1.Position;

        auto normal = glm::cross(U, V);

        p1.Normal = normal;
        p2.Normal = normal;
        p3.Normal = normal;
    }

    static inline std::vector<Vertex> GetUnitCircleVertices(uint32_t sectorCount) {
        float sectorStep = 2.f * std::numbers::pi_v<float> / static_cast<float>(sectorCount);
        float sectorAngle; // radians

        std::vector<Vertex> vertices{};

        for (auto i = 0; i <= sectorCount; i++) {
            sectorAngle = static_cast<float>(i) * sectorStep;
            vertices.push_back({
                                       .Position = {
                                               std::cos(sectorAngle),
                                               std::sin(sectorAngle),
                                               0
                                       }
                               });
        }

        return vertices;

    };

    static inline std::tuple<std::vector<Vertex>, std::vector<uint32_t>> BuildCylinderSmooth
            (uint32_t sectorCount, uint32_t topCenterIndex, uint32_t baseCenterIndex, float baseRadius, float height) {
        std::vector<Vertex> vertices{};
        std::vector<uint32_t> indices{};

        auto unitCircleVertices = GetUnitCircleVertices(sectorCount);

        /*
         *  building vertex array
         */

        // build the sides
        for (auto i = 0; i < 2; i++) {
            float h = -height / 2.f + static_cast<float>(i) * height;
            float t = 1.f - i; // texCoord

            // loop over all unit circle vertices
            uint32_t vertexIndex{ 0 };
            for (auto vertex: unitCircleVertices) {
                vertices.push_back({
                                           .Position = {
                                                   vertex.Position.x * baseRadius,
                                                   vertex.Position.y * baseRadius,
                                                   h,
                                           },
                                           .Color = {
                                                   vertexIndex % 3 == 0 ? 1.f : 0.f,
                                                   vertexIndex % 3 == 1 ? 1.f : 0.f,
                                                   vertexIndex % 3 == 2 ? 1.f : 0.f,
                                           },
                                           .Normal = {
                                                   vertex.Position.x * baseRadius,
                                                   vertex.Position.y * baseRadius,
                                                   vertex.Position.z * baseRadius,
                                           },
                                           .Uv = {
                                                   static_cast<float>(vertexIndex) / static_cast<float>(sectorCount),
                                                   t
                                           }
                                   });

                vertexIndex++;
            }
        }

        /*
         *  building index array
         */

        // indices for side surface

        uint32_t k1 = 0;
        uint32_t k2 = sectorCount + 1;
        for (auto i = 0; i < sectorCount; i++, k1++, k2++) {
            // 2 triangles per sector
            indices.push_back(k1);
            indices.push_back(k1 + 1);
            indices.push_back(k2);

            indices.push_back(k2);
            indices.push_back(k1 + 1);
            indices.push_back(k2 + 1);
        }

        // bottom surface
        for (uint32_t i = 0, k = baseCenterIndex + 1; i < sectorCount; i++, k++) {
            if (i < sectorCount - 1) {
                indices.push_back(baseCenterIndex);
                indices.push_back(k + 1);
                indices.push_back(k);
            } else {
                indices.push_back(baseCenterIndex);
                indices.push_back(baseCenterIndex + 1);
                indices.push_back(k);
            }
        }

        // top surface
        for (uint32_t i = 0, k = topCenterIndex + 1; i < sectorCount; i++, k++) {
            if (i < sectorCount - 1) {
                indices.push_back(topCenterIndex);
                indices.push_back(k);
                indices.push_back(k + 1);
            } else {
                indices.push_back(topCenterIndex);
                indices.push_back(k);
                indices.push_back(topCenterIndex + 1);
            }
        }

        return {vertices, indices};
    }

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
                    .Position = {-1.f, 1.f, 1.f},
                    .Color = {0.7f, 0.0f, 0.0f}, // darker red
                    .Uv = {0.f, 1.f}
            },
            {
                    .Position = {-1.f, -1.f, 1.f},
                    .Color = {1.0, 0.0f, 0.0f}, // red
                    .Uv = {0.f, 0.f}
            },
            {
                    .Position = {1.f, -1.f, 1.f},
                    .Color = {1.0f, 0.0f, 0.0f},
                    .Uv = {1.f, 0.f}
            },
            {
                    .Position = {1.f, 1.f, 1.f},
                    .Color = {1.0f, 0.0f, 0.0f},
                    .Uv = {1.f, 1.f}
            },

            // right face
            {
                    .Position = {1.f, 1.f, 1.f},
                    .Color = {0.6f, 0.3f, 0.6f}, // lighter purple
                    .Uv = {0.f, 1.f}
            },
            {
                    .Position = {1.f, -1.f, 1.f},
                    .Color = {0.5f, 0.25f, 0.5f}, // purple
                    .Uv = {0.f, 0.f}
            },
            {
                    .Position = {1.f, -1.f, -1.f},
                    .Color = {0.5f, 0.25f, 0.5f},
                    .Uv = {1.f, 0.f}
            },
            {
                    .Position = {1.f, 1.f, -.1f},
                    .Color = {0.5f, 0.25f, 0.5f},
                    .Uv = {1.f, 1.f}
            },

            // back face
            {
                    .Position = {1.f, 1.f, -1.f},
                    .Color = {0.8, 0.518, 0.0}, // darker orange
                    .Uv = {0.f, 1.f}
            },
            {
                    .Position = {1.f, -1.f, -1.f},
                    .Color = {1.0, 0.647, 0.0}, // orange
                    .Uv = {0.f, 0.f}
            },
            {
                    .Position = {-1.f, -1.f, -1.f},
                    .Color = {1.0, 0.647, 0.0},
                    .Uv = {1.f, 0.f}
            },
            {
                    .Position = {-1.f, 1.f, -1.f},
                    .Color = {1.0, 0.647, 0.0},
                    .Uv = {1.f, 1.f}
            },

            // left face
            {
                    .Position = {-1.f, 1.f, -1.f},
                    .Color = {0.8f, 0.8f, 0.4f}, // darker yellow
                    .Uv = {0.f, 1.f}
            },
            {
                    .Position = {-1.f, -1.f, -1.f}, // yellow
                    .Color = {1.0f, 1.0f, 0.5f},
                    .Uv = {0.f, 0.f}
            },
            {
                    .Position = {-1.f, -1.f, 1.f},
                    .Color = {1.0f, 1.0f, 0.5f},
                    .Uv = {1.f, 0.f}
            },
            {
                    .Position = {-1.f, 1.f, 1.f},
                    .Color = {1.0f, 1.0f, 0.5f},
                    .Uv = {1.f, 1.f}
            },

            // top face
            {
                    .Position = {-1.f, 1.f, -1.f},
                    .Color = {0.6f, 1.0f, 0.6f}, // lighter green
                    .Uv = {0.f, 1.f}
            },
            {
                    .Position = {-1.f, 1.f, 1.f},
                    .Color = {0.0f, 1.0f, 0.0f}, // green
                    .Uv = {0.f, 0.f}
            },
            {
                    .Position = {1.f, 1.f, 1.f},
                    .Color = {0.0f, 1.0f, 0.0f},
                    .Uv = {1.f, 0.f}
            },
            {
                    .Position = {1.f, 1.f, -1.f},
                    .Color = {0.0f, 1.0f, 0.0f},
                    .Uv = {1.f, 1.f}
            },

            // bottom face
            {
                    .Position = {1.f, -1.f, 1.f},
                    .Color = {0.2f, 0.2f, 0.2f}, // lighter black (grey)
                    .Uv = {0.f, 1.f}
            },
            {
                    .Position = {1.f, -1.f, -1.f},
                    .Color = {0.0f, 0.0f, 0.0f}, // black
                    .Uv = {0.f, 0.f}
            },
            {
                    .Position = {-1.f, -1.f, -1.f},
                    .Color = {0.0f, 0.0f, 0.0f},
                    .Uv = {1.f, 0.f}
            },
            {
                    .Position = {-1.f, -1.f, 1.f},
                    .Color = {0.0f, 0.0f, 0.0f},
                    .Uv = {1.f, 1.f}
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
                    //.Uv = {1.f, 1.f}
            },
            {
                    .Position = {-0.5f, -0.5f, 0.5f},
                    .Color = {1.0, 1.0, 0.8}, // sand
                    //.Uv = {0.5f, 0.f}
            },
            {
                    .Position = {0.5f, -0.5f, 0.5f},
                    .Color = {1.0, 1.0, 0.8}, // sand
                    //.Uv = {1.f, 0.f}
            },

            // right face
            { // pyramid tip
                    .Position = {0.f, 0.5f, 0.f},
                    .Color = {1.0, 1.0, 0.8}, // sand
                    //.Uv = {1.f, 1.f}
            },
            {
                    .Position = {0.5f, -0.5f, 0.5f},
                    .Color = {1.0, 1.0, 0.8}, // sand
                    //.Uv = {.5f, 0.f}
            },
            {
                    .Position = {0.5f, -0.5f, -0.5f},
                    .Color = {1.0, 1.0, 0.8}, // sand
                    //.Uv = {1.f, 0.f}
            },

            // back face
            { // pyramid tip
                    .Position = {0.f, 0.5f, 0.f},
                    .Color = {1.0, 1.0, 0.8}, // sand
                    //.Uv = {1.f, 1.f}
            },
            {
                    .Position = {0.5f, -0.5f, -0.5f},
                    .Color = {1.0, 1.0, 0.8}, // sand
                    //.Uv = {.5f, 0.f}
            },
            {
                    .Position = {-0.5f, -0.5f, -0.5f},
                    .Color = {1.0, 1.0, 0.8}, // sand
                    //.Uv = {1.f, 0.f}
            },

            // left face
            { // pyramid tip
                    .Position = {0.f, 0.5f, 0.f},
                    .Color = {1.0, 1.0, 0.8}, // sand
                    //.Uv = {1.f, 1.f}
            },
            {
                    .Position = {-0.5f, -0.5f, -0.5f},
                    .Color = {1.0, 1.0, 0.8}, // sand
                    //.Uv = {.5f, 0.f}
            },
            {
                    .Position = {-0.5f, -0.5f, 0.5f},
                    .Color = {1.0, 1.0, 0.8}, // sand
                    //.Uv = {1.f, 0.f}
            },

            // bottom face
            {
                    .Position = {0.5f, -0.5f, 0.5f},
                    .Color = {1.0, 1.0, 0.8}, // sand
                    //.Uv = {0.f, 1.f}
            },
            {
                    .Position = {0.5f, -0.5f, -0.5f},
                    .Color = {1.0, 1.0, 0.8}, // sand
                    //.Uv = {0.f, 0.f}
            },
            {
                    .Position = {-0.5f, -0.5f, -0.5f},
                    .Color = {1.0, 1.0, 0.8}, // sand
                    //.Uv = {1.f, 0.f}
            },
            {
                    .Position = {-0.5f, -0.5f, 0.5f},
                    .Color = {1.0, 1.0, 0.8}, // sand
                    //.Uv = {1.f, 1.f}
            }
    };


    static inline std::vector<uint32_t> pyramidElements{
            // indices
            0, 1, 2, // front face
            3, 4, 5, // right face
            6, 7, 8, // back face
            9, 10, 11, // left face
            13, 12, 15, 14, 13, 15 // bottom face
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

        float sectorStep = 2 * std::numbers::pi / sectorCount;
        float stackStep = std::numbers::pi / stackCount;

        for (int i = 0; i <= stackCount; ++i) {
            float stackAngle = std::numbers::pi / 2 - i * stackStep;
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
