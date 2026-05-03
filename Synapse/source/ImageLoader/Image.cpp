#include "Image.h"
#include <iostream>

Image::Image(const char* imagePath)
{
    stbi_set_flip_vertically_on_load(true);
    Texture = stbi_load(imagePath, &width, &height, &nrChannels, 0);
    
    if (!Texture) {
        std::cout << "Failed to load: " << imagePath << std::endl;
        return;
    }

    glGenTextures(1, &ID);

    glBindTexture(GL_TEXTURE_2D, ID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Texture);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    FreeTexture();
}

void Image::FreeTexture()
{
    stbi_image_free(Texture);
    Texture = nullptr;
}
