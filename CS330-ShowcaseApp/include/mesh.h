//
// Created by maxan on 11/8/2023.
//

#pragma once
#include <vector>
#include <types.h>
#include <glad/glad.h>

class Mesh {
public:
    // Mesh() = default;
    Mesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& elements);

    void Draw();

    // basic camera
    glm::mat4 Transform {1.f};

private:

    uint32_t _elementCount {0};
    GLuint _vertexBufferObject {};
    GLuint _shaderProgram {};
    GLuint _vertexArrayObject {};
    // below is what helps with vertices sharing a space (being on the same vertex point)
    // it is so that the normals will behave correctly for lighting
    GLuint _elementBufferObject {};
};



