#pragma once

#include "glm/glm.hpp"
#include "../Actor/Actor.h"
#include <string>
#include "../Enums&Structs/GameTypes.h"


class Animator: public Object
{
public:

	Animator() {};
	Animator(glm::vec2 TileXY);

	void UpdateUV(glm::vec2 TileXY);

	glm::vec2 tileXY{1, 1};
	glm::vec2 uvScale{1, 1};
	glm::vec2 uvOffset{0, 0};

	void Tick(double deltaTime) override;

	std::unordered_map<std::string, AnimationClip> animations; 

private:
	float frameTime = 0.15f;  // seconds per frame
	float timer = 0.0f;
};

