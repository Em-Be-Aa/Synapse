#pragma once

#include "../Collision/CollisionComponent.h"
#include "../Sprite/Animator.h"
#include <memory>
#include <string>

class Character;

class Ability : public Object
{

public:

	Ability(std::string abilTag, Animator* animator);
	void Update(double deltaTime) override;
	void Activate(Character* instigator);

	unsigned ID = 0;
	std::string tag = "";
	Animator* targetAnimator;

	bool GetCooldownStatus() 
	{
		return isOnCooldown;
	};

private:

	float targetCooldownTime = 2.0f;
	float currentCooldownTime = 0.0f;
	bool isOnCooldown= false;

	float targetActivationTime = 1.0f;
	float currentActivationTime = 0.0f;
	bool isActivated = false;
	Character* owner;

	AbilityCollisionInfo abilInfo;

	CollisionComponent* abilityCollidor;

};

