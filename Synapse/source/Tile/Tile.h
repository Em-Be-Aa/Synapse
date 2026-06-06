#pragma once

#include "../Sprite/Sprite.h"
#include "../Enums&Structs/GameTypes.h"





class Tile : public Sprite
{

public:

    Tile(const char* imagePath) : Sprite(imagePath) {};


private:

    TileType Type;
    
};
