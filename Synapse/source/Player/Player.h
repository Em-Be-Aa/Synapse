#pragma once

#include "../Sprite/Sprite.h"
#include "../Shader/Shader.h"

class Player : public Sprite
{

public:

	Player(const char* imagePath, Shader* defaultShader);

	glm::vec3 playerPosition = glm::vec3(0.0f, 0.0f, 0.0003f);

	void Tick() override;

private:

	Shader* defaultShader;

};

