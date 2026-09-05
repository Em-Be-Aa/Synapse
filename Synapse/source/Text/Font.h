#pragma once

#include <string>
#include <vector>

#include "stb_truetype.h"

class Font
{
public:
    bool Init(const char* ttfPath, float pixelheight = 32.0f);

    unsigned int GetTextureID() const { return textureID; }
    const stbtt_bakedchar* GetBakedChars() const { return bakedChars; }
    int GetAtlasWidth() const { return atlasWidth; }
    int GetAtlasHeight() const { return atlasHeight; }
    float GetPixelHeight() const { return pixelHeight; }

private:

    float pixelHeight = 32.0f;
    unsigned int textureID = 0;
    stbtt_bakedchar* bakedChars = nullptr; // covers ASCII 32..126
    int atlasWidth = 512;
    int atlasHeight = 512;
    float ascentPixels = 0.0f;
    float descentPixels = 0.0f;


public:

    float GetAscentPixels()
    {
        return ascentPixels;
    }

    float GetDescentPixels()
    {
        return descentPixels;
    }
};