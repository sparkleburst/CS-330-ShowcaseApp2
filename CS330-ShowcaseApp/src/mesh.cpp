//
// Created by maxan on 11/8/2023.
//

#include <mesh.h>
#include <iostream>

// mesh.cpp constructors

Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<uint32_t> &elements) {
    init(vertices, elements);
}

Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<uint32_t> &elements, const glm::vec3 &color) {
    // override color
    for (auto& vertex : vertices) {
        vertex.Color = color;
    }

    init(vertices, elements);
}

void Mesh::Draw() {
    /* moved to shaders.cpp
     *
    // use our triangle shaders
    glUseProgram(_shaderProgram);
     */

    // bind vertex array
    glBindVertexArray(_vertexArrayObject);

    // gl draw calls
    glDrawElements(GL_TRIANGLES, _elementCount, GL_UNSIGNED_INT, nullptr);

}

void Mesh::init(std::vector<Vertex>& vertices, std::vector<uint32_t>& elements) {
    // create the triangle
    glGenVertexArrays(1, &_vertexArrayObject);
    // initialize above with below
    glGenBuffers(1, &_vertexBufferObject); // the 1 means we want 1 buffer
    // for an array we would increase that number
    glGenBuffers(1, &_elementBufferObject);

    glBindVertexArray(_vertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(vertices.size() * sizeof(Vertex)), vertices.data(),
                 GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(elements.size() * sizeof(uint32_t)), elements.data(),
                 GL_STATIC_DRAW);

    // define vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, Position)));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, Color)));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, Normal)));
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, Uv)));

    // enable vertex attributes
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    _elementCount = elements.size();
}
