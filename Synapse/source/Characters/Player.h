#pragma once

#include "../Sprite/Sprite.h"
#include "../Shader/Shader.h"
#include "Character.h"
#include "../Camera/Camera.h"

class Player : public Character
{

public:

	Player();

	void Tick(double deltaTime) override;
	void onInputAction(int Key) override;

};

