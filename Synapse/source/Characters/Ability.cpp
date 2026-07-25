#include "../Characters/Character.h"
#include "../Collision/CollisionComponent.h"
#include "../Templates/Templates.h"
#include "Ability.h"
#include <iostream>


Ability::Ability(std::string abilTag, Animator* animator)
{
	tag = abilTag;
	targetAnimator = animator;
}

void Ability::Update(double deltaTime)
{
	if (isOnCooldown && currentCooldownTime <= targetCooldownTime)
	{
		currentCooldownTime += deltaTime;
	}
	else
	{
		currentCooldownTime = 0.0f;
		isOnCooldown = false;
	}


	if (isActivated && currentActivationTime <= targetActivationTime)
	{
		currentActivationTime += deltaTime;
	}
	else
	{
		if(currentActivationTime > targetActivationTime)
			abilityCollidor->isPendingDestroy = true;

		currentActivationTime = 0.0f;
		isActivated = false;

	}

	
}

void Ability::Activate(Character* instigator)
{
	if (!isOnCooldown)
	{
		isOnCooldown = !isOnCooldown;
		isActivated = true;

		if (targetAnimator)
		{
			targetAnimator->SetCurrentAnim(tag);
			abilityCollidor = SpawnActor<CollisionComponent>();

			//ability collision box size and offset should be saved with ability info so we dont have to hardcode it in this function.... also things like activation time and stuff like that
			abilityCollidor->BoxSize = { 0.1 , 0.1 };
			float halfX = abilityCollidor->BoxSize.x * 0.5f;
			float halfY = abilityCollidor->BoxSize.y * 0.5f;
			abilityCollidor->Box.min = { instigator->Position.x - halfX, instigator->Position.y - halfY };
			abilityCollidor->Box.max = { instigator->Position.x + halfX, instigator->Position.y + halfY };
		}
	}
	
}
