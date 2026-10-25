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

	Ability(std::string abilTag, std::weak_ptr<Animator> animator, std::string charTag, std::weak_ptr<Character> Owner, AbilityInfo info);
	void Update(double deltaTime) override;
	virtual void Activate();
	void OnAbilityMontageCompleted(std::string Anim);

	unsigned ID = 0;
	std::string tag = "";
	std::weak_ptr<Animator> targetAnimator;

protected:

	float currentCooldownTime = 0.0f;
	bool isOnCooldown= false;
	float targetCollidorTime = 1.0f;
	float currentCollidorTime = 0.0f;
	bool isCollidorActivated = false;
	bool isAbilityActivated = false;

	std::weak_ptr<Character> owner;
	AbilityInfo abilInfo;
	std::shared_ptr<CollisionComponent> abilityCollidor;


public:

	bool GetCooldownStatus()
	{
		return isOnCooldown;
	};

	float GetCurrentCooldown()
	{

		return isOnCooldown ? abilInfo.abilityCooldown - currentCooldownTime : 0.0f;
	}

	bool IsAbilityActivated()
	{
		return isAbilityActivated;
	}

};

