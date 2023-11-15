//
// Created by maxan on 11/9/2023.
//

#include <shader.h>
#include <iostream>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const std::string &vertexSource, const std::string &fragmentSource) {
    load(vertexSource, fragmentSource);
}

Shader::Shader(const Path& vertexPath, const Path& fragmentPath) {

    try{
        // load sources from files
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;

        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);

        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        // load our shader

        load(vShaderStream.str(), fShaderStream.str());
    }
    catch (std::ifstream::failure& e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    }
}

void Shader::Bind() {
    // use the triangle shaders
    glUseProgram(_shaderProgram);
}

void Shader::load(const std::string &vertexSource, const std::string &fragmentSource) {

    const char* vShaderCode = vertexSource.c_str();
    const char* fShaderCode = fragmentSource.c_str();

    auto vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // compile the vertex shaders

    glShaderSource(vertexShader, 1, &vShaderCode, nullptr);
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

    // compile the fragment shader

    glShaderSource(fragmentShader, 1, &fShaderCode, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog
                  << std::endl;
    }

// Link shaders
    _shaderProgram = glCreateProgram();
    glAttachShader(_shaderProgram, vertexShader);
    glAttachShader(_shaderProgram, fragmentShader);
    glLinkProgram(_shaderProgram);

// Check for linking errors
    glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(_shaderProgram, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
    }

// Delete the shaders after linking
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

}

GLint Shader::getUniformLocation(const std::string &uniformName) {

    return glGetUniformLocation(_shaderProgram, uniformName.c_str());
}

void Shader::SetMat4(const std::string& uniformName,const glm::mat4 &mat4) {
    auto uniformLoc = getUniformLocation(uniformName);

    if (uniformLoc != -1) {
        Bind();
        glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(mat4));
    }
}
