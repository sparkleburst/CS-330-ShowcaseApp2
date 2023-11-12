//
// Created by maxan on 11/9/2023.
//

#pragma once
#include <filesystem>
#include <string>
#include <GLAD/glad.h>

using Path = std::filesystem::path;

class Shader {
public:
    Shader() = default;
    Shader(const std::string& vertexSource, const std::string& fragmentSource);
    Shader(const Path& vertexPath, const Path& fragmentPath);

    void Bind();

private:
    void load(const std::string& vertexSource, const std::string& fragmentSource);

private:
    GLuint _shaderProgram;
};


