#include "../../Characters/Character.h"
#include "../../Collision/CollisionComponent.h"
#include "../../GameConfig/GameConfigs.h"
#include "../../Templates/Templates.h"
#include "../Enemy.h"
#include "../Player.h"
#include "Ability.h"
#include <iostream>
#include <random>


Ability::Ability(std::string abilTag, Animator* animator, std::string charTag, Character* Owner, AbilityInfo info)
{
	tag = abilTag;
	targetAnimator = animator;
	owner = Owner;
	abilInfo = info;

	owner->GetVitalsComponent().onAbilityModified.Subscribe
	(
		[this](AbilityVital info)
		{
			if (info.tag == tag)
			{
				abilInfo.abilityDamage = info.abilityDamage;
				abilInfo.abilityCooldown = info.abilityCooldown;
				abilInfo.dashDistance = info.dashDistance;

				std::cout << "Ability Modified : " << abilInfo.abilityDamage << " | "
					<< abilInfo.abilityCooldown << " | " << abilInfo.dashDistance.value_or(0.0f) << std::endl;
			}
			
		}
	);
}

void Ability::Update(double deltaTime)
{
	if (isOnCooldown && currentCooldownTime <= abilInfo.abilityCooldown)
	{
		currentCooldownTime += deltaTime;
	}
	else
	{
		currentCooldownTime = 0.0f;
		isOnCooldown = false;
	}

	// Also add this in ability info
	if (isActivated && currentActivationTime <= targetActivationTime)
	{
		currentActivationTime += deltaTime;
	}
	else
	{
		if (abilityCollidor && currentActivationTime > targetActivationTime)
		{
			abilityCollidor->Destroy();
			abilityCollidor = nullptr;
		}


		currentActivationTime = 0.0f;
		isActivated = false;

	}

	if (owner && abilityCollidor)
	{
		float halfX = abilityCollidor->BoxSize.x * 0.5f;
		float halfY = abilityCollidor->BoxSize.y * 0.5f;
		abilityCollidor->Box.min = { owner->Position.x - halfX + (abilInfo.collidorOffset->x * owner->GetCharacterDirection()), owner->Position.y - halfY + abilInfo.collidorOffset->y };
		abilityCollidor->Box.max = { owner->Position.x + halfX + (abilInfo.collidorOffset->x * owner->GetCharacterDirection()), owner->Position.y + halfY + abilInfo.collidorOffset->y };
	}
}

// Make 3 child classes light heavy and dash ability so logic is simpler...core logic resides here...
void Ability::Activate()
{
	if (!isOnCooldown)
	{
		isOnCooldown = !isOnCooldown;
		isActivated = true;

		if (targetAnimator)
		{
			targetAnimator->SetCurrentAnim(tag, false);

			std::random_device rd;
			std::mt19937 gen(rd());
			std::bernoulli_distribution proc_chance(owner->GetVitalsComponent().GetFocus());
			float totalDamage = abilInfo.abilityDamage;

			if (proc_chance(gen))
			{
				totalDamage = 2 * abilInfo.abilityDamage;
			}
			

			abilityCollidor = SpawnActor<CollisionComponent>(owner, true, totalDamage);

			//ability collision box size and offset should be saved with ability info so we dont have to hardcode it in this function.... also things like activation time and stuff like that
			abilityCollidor->BoxSize = abilInfo.collidorSize.value_or(glm::vec2(0.0f));
			float halfX = abilityCollidor->BoxSize.x * 0.5f;
			float halfY = abilityCollidor->BoxSize.y * 0.5f;
			abilityCollidor->Box.min = { owner->Position.x - halfX + (abilInfo.collidorOffset->x * owner->GetCharacterDirection()), owner->Position.y - halfY + abilInfo.collidorOffset->y };
			abilityCollidor->Box.max = { owner->Position.x + halfX + (abilInfo.collidorOffset->x * owner->GetCharacterDirection()), owner->Position.y + halfY + abilInfo.collidorOffset->y };
		}
	}
	
}
