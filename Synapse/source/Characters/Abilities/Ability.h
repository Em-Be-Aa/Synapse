#pragma once

#include "../../Collision/CollisionComponent.h"
#include "../../Sprite/Animator.h"
#include <iostream>
#include <memory>
#include <string>

class Character;

class Ability : public Object
{

public:

	Ability(std::string abilTag, Animator* animator, std::string charTag, Character* Owner, AbilityInfo info);
	void Update(double deltaTime) override;
	virtual void Activate();

	unsigned ID = 0;
	std::string tag = "";
	Animator* targetAnimator;

	bool GetCooldownStatus() 
	{
		return isOnCooldown;
	};

	float GetCurrentCooldownPerc()
	{

		return isOnCooldown ? currentCooldownTime / abilInfo.abilityCooldown : 0.0f;
	}

protected:

	float currentCooldownTime = 0.0f;
	bool isOnCooldown= false;
	float targetActivationTime = 1.0f;
	float currentActivationTime = 0.0f;
	bool isActivated = false;

	Character* owner;
	AbilityInfo abilInfo;
	CollisionComponent* abilityCollidor;

};

