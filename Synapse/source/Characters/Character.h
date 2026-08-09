#pragma once

#include "../Collision/CollisionComponent.h"
#include "../Enums&Structs/GameTypes.h"
#include "../Shader/RenderComponent.h"
#include "../Sprite/Sprite.h"
#include "AbilityComponent.h"
#include "HealthComponent.h"


class Character: public Actor
{

public:

	Character();
	void Tick(double deltaTime) override;
	void Update(double deltaTime) override;
	void Destroy() override;

	void OnCollision(CollisionInfo Info);
	void OnCharacterDeath();
	void OnAnimationMontageComplete(std::string Anim);

protected:

	Sprite characterSprite;
	CollisionComponent* Collidor;
	RenderComponent RenderComp;
	HealthComponent HealthComp;
	AbilityComponent AbilComp;

	glm::vec3 characterFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 characterUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 previousPosition = glm::vec3(0.0f, 0.0f, 0.0003f);



// Getters and Setters
public:

	AbilityComponent& GetAbilityComponent()
	{
		return AbilComp;
	};

	Sprite& GetSpriteComponent()
	{
		return characterSprite;
	};

};
