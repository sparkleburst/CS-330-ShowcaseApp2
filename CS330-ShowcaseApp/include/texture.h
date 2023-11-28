//
// Created by maxan on 11/28/2023.
//

#pragma once

#include <filesystem>
#include <glad/glad.h>


class Texture {
public:
    explicit Texture(const std::filesystem::path& path);
    void Bind();

private:
    GLuint _textureHandle;
};



