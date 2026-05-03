#pragma once

#include "../Sprite/Sprite.h"
#include "../Shader/Shader.h"
#include "Character.h"
#include "../Camera/Camera.h"

class Player : public Character
{

public:

	Player(const char* imagePath, Shader* defaultShader, Camera* Camera);

	void Tick(double deltaTime) override;

};

