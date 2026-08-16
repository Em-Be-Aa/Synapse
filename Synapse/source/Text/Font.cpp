#include "Font.h"
#include <fstream>
#include <glad/glad.h>
#include <iostream>
#include <vector>

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

bool Font::Init(const char* ttfPath, float pixelheight)
{
    std::ifstream file(ttfPath, std::ios::binary | std::ios::ate);
    if (!file.is_open())
    {
        std::cout << "Font: could not open " << ttfPath << std::endl;
        return false;
    }

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<unsigned char> fontBuffer(size);
    if (!file.read(reinterpret_cast<char*>(fontBuffer.data()), size))
    {
        std::cout << "Font: failed reading " << ttfPath << std::endl;
        return false;
    }

    pixelHeight = pixelheight;

    std::vector<unsigned char> singleChannelBitmap(atlasWidth * atlasHeight);
    bakedChars = new stbtt_bakedchar[96]; // ASCII 32 (space) .. 127

    int result = stbtt_BakeFontBitmap(
        fontBuffer.data(), 0,
        pixelheight,
        singleChannelBitmap.data(), atlasWidth, atlasHeight,
        32, 96,
        bakedChars
    );

    if (result <= 0)
    {
        std::cout << "Font: BakeFontBitmap failed for " << ttfPath
            << " (atlas too small, or bad font data)" << std::endl;
        delete[] bakedChars;
        bakedChars = nullptr;
        return false;
    }

    std::vector<unsigned char> rgbaBitmap(atlasWidth * atlasHeight * 4);
    for (int i = 0; i < atlasWidth * atlasHeight; i++)
    {
        unsigned char coverage = singleChannelBitmap[i];
        rgbaBitmap[i * 4 + 0] = 255;       // R
        rgbaBitmap[i * 4 + 1] = 255;       // G
        rgbaBitmap[i * 4 + 2] = 255;       // B
        rgbaBitmap[i * 4 + 3] = coverage;  // A
    }

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, atlasWidth, atlasHeight, 0,
        GL_RGBA, GL_UNSIGNED_BYTE, rgbaBitmap.data());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, 0);

    return true;
}