#pragma once

#include "../Collision/CollisionComponent.h"
#include "../Enums&Structs/GameTypes.h"
#include "../Shader/RenderComponent.h"
#include "../Sprite/Sprite.h"
#include "Components/AbilityComponent.h"
#include "Components/VitalsComponent.h"


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
	VitalsComponent VitalsComp;
	AbilityComponent AbilComp;

	std::string tag = "character";
	glm::vec3 characterFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 characterUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 previousPosition = glm::vec3(0.0f, 0.0f, 0.0003f);
	Faction characterFaction = Faction::None;

private:

	bool isFacingRight = true;
	bool isCharacterAlive = true;


public:

	AbilityComponent& GetAbilityComponent()
	{
		return AbilComp;
	};

	Sprite& GetSpriteComponent()
	{
		return characterSprite;
	};

	CollisionComponent& GetCollisionComponent()
	{
		return *Collidor;
	}

	VitalsComponent& GetVitalsComponent()
	{
		return VitalsComp;
	}

	int GetCharacterDirection()
	{
		return isFacingRight ? 1 : -1;
	}

	bool GetAliveStatus()
	{
		return isCharacterAlive;
	}

	void SetAliveStatus(bool Status)
	{
		isCharacterAlive = Status;
	}

	Faction GetFaction()
	{
		return characterFaction;
	}

	std::string GetCharacterTag() { return tag; }

};
