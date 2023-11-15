//
// Created by maxan on 11/8/2023.
//

#include <mesh.h>
#include <iostream>

// mesh.cpp constructor
Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<uint32_t> &elements) {
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

    /*
     * moved to application.cpp
    // create vertex shaders with string literals - (R"(asd)")
    auto vertexShaderSource = R"(#version 330 core
    layout (location = 0) in vec3 position;
    layout (location = 1) in vec3 color;
    layout (location = 2) in vec3 normal;
    layout (location = 3) in vec3 uv;

    out vec4 vertexColor;
    void main() {
        gl_Position = vec4(position.x, position.y, position.z, 1.0f);
        vertexColor = vec4(color, 1.0f);
    }
    )";

    // define vertex shaders
    auto fragmentShaderSource = R"(#version 330 core

    out vec4 FragColor;
    in vec4 vertexColor;

    void main() {
        FragColor = vertexColor;
    }
    )";
    // FragColor is making the color of the vertices
    */

/*
 * moved to shaders.cpp
    auto vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // compile the vertex shaders

    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog
                  << std::endl;
    }

    auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // compile the vertex shaders

    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog
                  << std::endl;
    }

    _shaderProgram = glCreateProgram();
    glAttachShader(_shaderProgram, vertexShader);
    glAttachShader(_shaderProgram, fragmentShader);
    glLinkProgram(_shaderProgram);

    glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::LINK_FAILED\n" << infoLog
                  << std::endl;
    }

    // next delete the shaders after we've created them as we don't need them anymore
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
*/
    _elementCount = elements.size();
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