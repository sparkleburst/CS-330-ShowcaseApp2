//
// Created by maxan on 11/28/2023.
//

#include <texture.h>
#include <stb_image.h>
#include <iostream>

Texture::Texture(const std::filesystem::path &path) {
    // load a texture
    stbi_set_flip_vertically_on_load(true); // keeps image up the way you expect it

    auto texturePath = path.string();
    int width, height, numChannels; // rgba has 4 channels, etc
    unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &numChannels,
                                    STBI_rgb_alpha);

    glGenTextures(1, &_textureHandle);
    glBindTexture(GL_TEXTURE_2D, _textureHandle);

    if (data) {
        // line below is deprecated, next two are more modern
        // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

        // allocate appropriate amount of space for the textures on the GPU
        glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, width, height);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cerr << "Failed to load texture at path: " << texturePath << std::endl;
    }

    stbi_image_free(data);
}

void Texture::Bind() {

    glBindTexture(GL_TEXTURE_2D, _textureHandle);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

}
