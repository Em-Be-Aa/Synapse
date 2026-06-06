#include "Animator.h"
#include <iostream>

Animator::Animator(glm::vec2 TileXY)
{
	tileXY = TileXY;
	uvScale = { 1.0f / TileXY.x, 1.0f / TileXY.y};
	uvOffset = {0, 0};
}


void Animator::UpdateUV(glm::vec2 TileXY)
{
    tileXY = TileXY;
    uvScale = { 1.0f / TileXY.x, 1.0f / TileXY.y };
    uvOffset = { 0, 0 };
}

void Animator::Tick(double deltaTime)
{	
    // Animation Speed
    timer += 0.021;

    if (timer >= frameTime) {
        timer = 0.0f;
       
        // Sprite UV Calculation
        uvOffset.x += uvScale.x;

        if (uvOffset.x >= 1.0f) {
            uvOffset.x = 0;
            uvOffset.y += uvScale.y;
        }

        if (uvOffset.y >= 1.0f) {
            uvOffset.y = 0;
        }
    }
}
