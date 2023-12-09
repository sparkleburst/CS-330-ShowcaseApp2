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

    // std::cerr << vertexPath << std::endl;

    try{
        // load sources from files
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;

        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);

        if (!vShaderFile.is_open()) {
            // File failed to open
            // Handle the error here, such as printing an error message
            std::cerr << "Failed to open file: " << vertexPath << std::endl;
            // Further error handling or program logic
        }

        if (!fShaderFile.is_open()) {
            // File failed to open
            // Handle the error here, such as printing an error message
            std::cerr << "Failed to open file: " << fragmentPath << std::endl;
            // Further error handling or program logic
        }

        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        // load our shader

        load(vShaderStream.str(), fShaderStream.str());
    }
    catch (std::ifstream::failure& e) {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    }
}

void Shader::Bind() const {
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
        std::cerr << "``" << vertexSource << "''" << std::endl;
        std::cerr << "``" << fragmentSource << "''" << std::endl;
    }

// Delete the shaders after linking
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

GLint Shader::getUniformLocation(const std::string &uniformName) const{
    return glGetUniformLocation(_shaderProgram, uniformName.c_str());
}

void Shader::AddTexture(const std::shared_ptr<Texture> &texture) {
    _textures.emplace_back(texture);
}

void Shader::SetVec3(const std::string &uniformName, const glm::vec3 &vec3) const {
    auto uniformLoc = getUniformLocation(uniformName);

    if (uniformLoc != -1) {
        glUniform3fv(uniformLoc, 1, glm::value_ptr(vec3));
    }
}

void Shader::SetMat4(const std::string& uniformName,const glm::mat4 &mat4) const {
    auto uniformLoc = getUniformLocation(uniformName);

    if (uniformLoc != -1) {
        glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(mat4));
    }
}

void Shader::SetInt(const std::string &uniformName, int value) const{
    auto uniformLoc = getUniformLocation(uniformName);

    if (uniformLoc != -1) {
        glUniform1i(uniformLoc, value);
    }
}

void Shader::UseTextures(int numTextures) const{
    for (auto i = 0; i < numTextures && i < _textures.size(); i++) {
        std::string uniformName = "tex";
        uniformName += std::to_string(i);

        SetInt(uniformName, i);
    }
}

