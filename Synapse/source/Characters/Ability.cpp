#include "../Characters/Character.h"
#include "../Collision/CollisionComponent.h"
#include "../GameConfig/GameConfigs.h"
#include "../Templates/Templates.h"
#include "Ability.h"
#include <iostream>


Ability::Ability(std::string abilTag, Animator* animator)
{
	tag = abilTag;
	targetAnimator = animator;

	//there is a chance that this is not loaded and null...so be careful
	abilInfo = GameConfigs::GetGameConfig().GetCharacterAbilityData(abilTag);
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
			abilityCollidor->Destroy();

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
			abilityCollidor = SpawnActor<CollisionComponent>(instigator, true);

			//ability collision box size and offset should be saved with ability info so we dont have to hardcode it in this function.... also things like activation time and stuff like that
			abilityCollidor->BoxSize = abilInfo.collidorSize;
			float halfX = abilityCollidor->BoxSize.x * 0.5f;
			float halfY = abilityCollidor->BoxSize.y * 0.5f;
			abilityCollidor->Box.min = { instigator->Position.x - halfX + abilInfo.collidorOffset.x, instigator->Position.y - halfY + abilInfo.collidorOffset.y };
			abilityCollidor->Box.max = { instigator->Position.x + halfX + abilInfo.collidorOffset.x, instigator->Position.y + halfY + abilInfo.collidorOffset.y };
		}
	}
	
}
