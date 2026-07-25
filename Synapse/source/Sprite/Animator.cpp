#include "Animator.h"
#include <iostream>

Animator::Animator(glm::vec2 TileXY)
{
	tileXY = TileXY;
	uvScale = { 1.0f / TileXY.x, 1.0f / TileXY.y};
	uvOffset = {0, 0};
}


// Animation system..understand it again and make it a bit cleaner....map is not clean and should be configurable by child classes....also add consistent checks for nullptr if there is a chance
void Animator::UpdateAnim(std::string Mode)
{
	auto It = animMontage.find(Mode);
	if (It != animMontage.end())
	{
		currentAnim = Mode;
		currentMontage = It->second;
		tileXY = It->second.imageTiles;

		uvScale = { 1.0f / tileXY.x, 1.0f / tileXY.y };
		uvOffset = { 0, 0 };
	}
	else
	{
		std::cout << "Failed to find Animation State" << std::endl;
	}
}

void Animator::Update(double deltaTime)
{
	
	//std::cout << "current state: " << currentAnim << std::endl;

	// Animation Speed
	timer += 0.021;

	if (timer >= frameTime) {
		timer = 0.0f;
	   
		// Sprite UV Calculation
		uvOffset.x += uvScale.x;

		if (uvOffset.x >= 1.0f) {

			// If montage plays, at the end swtich back to previous state
			if (currentMontage.isMontage)
			{
				SetCurrentAnim(prevAnim);
			}

			uvOffset.x = 0;
			uvOffset.y += uvScale.y;
		}

		// Used if sprite sheet have multiple rows...have not been tested
		if (uvOffset.y >= 1.0f) {
			uvOffset.y = 0;
		}
	}
}
