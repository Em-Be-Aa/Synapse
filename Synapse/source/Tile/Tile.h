#pragma once
#include "../Sprite/Sprite.h"
#include "../Shader/Shader.h"



enum TileType {
    None,
    Grass,
    Land,
    Water
};


class Tile : public Sprite
{

public:

    Tile(const char* imagePath);

    TileType Type;

private:
    
    glm::vec2 SpriteTile{ 1, 1 };
};
