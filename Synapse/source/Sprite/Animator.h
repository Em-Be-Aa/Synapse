#pragma once

#include "../Actor/Actor.h"
#include "../Enums&Structs/GameTypes.h"
#include "../Interfaces/IAnimate.h"
#include "glm/glm.hpp"
#include <map>
#include <string>

// Clean this mess...
class Animator: public Object, public IAnimate
{
public:

	Animator() {};
	Animator(glm::vec2 TileXY);

	glm::vec2 tileXY{1, 1};
	glm::vec2 uvScale{1, 1};
	glm::vec2 uvOffset{0, 0};

	void UpdateAnim(std::string Mode);
	void Update(double deltaTime) override;

	void PlayAnimation(std::string Mode) override
	{
		prevAnim = currentAnim;
		currentAnim = Mode;
		UpdateAnim(Mode);
	};

	void SetCurrentAnim(std::string Mode) 
	{
		prevAnim = currentAnim;
		currentAnim = Mode;
		UpdateAnim(Mode);
	}

	std::string GetCurrentAnim()
	{
		return currentAnim;
	}


	std::unordered_map<std::string, AnimationClip> animations;
	std::map<std::string, Anim_Clip> animMontage = {};
	Anim_Clip currentMontage;

private:

	float frameTime = 0.15f;  // seconds per frame
	float timer = 0.0f;

	std::string currentAnim = "IDLE";
	std::string prevAnim = "IDLE";

};

