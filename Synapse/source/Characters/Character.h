#pragma once

#include "../Camera/Camera.h"
#include "../Collision/CollisionComponent.h"
#include "../Enums&Structs/GameTypes.h"
#include "../Shader/RenderComponent.h"
#include "../Shader/Shader.h"
#include "../Sprite/Sprite.h"
#include "AbilityComponent.h"
#include "HealthComponent.h"
#include <map>

class Character : public Actor
{

public:

	Character();
	void Tick(double deltaTime) override;

	AbilityComponent& GetAbilityComponent()
	{
		return AbilComp;
	};

	Sprite& GetSpriteComponent()
	{
		return characterSprite;
	};

protected:

	Sprite characterSprite;
	CollisionComponent Collidor;
	RenderComponent RenderComp;
	HealthComponent HealthComp;
	AbilityComponent AbilComp;

	glm::vec3 characterFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 characterUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 previousPosition = glm::vec3(0.0f, 0.0f, 0.0003f);
};
