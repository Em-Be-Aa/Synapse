#pragma once

#include "../Camera/Camera.h"
#include "../Shader/Shader.h"
#include "../Sprite/Sprite.h"
#include "Character.h"

class Player: public Character
{

public:

	Player();

	void Tick(double deltaTime) override;
	void onInputClicked(int Key) override;
	void onInputPressed(int Key) override;
	void onInputReleased(int Key) override;


};

