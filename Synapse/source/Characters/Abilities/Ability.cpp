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

	owner->GetSpriteComponent().spriteAnimator->onMontageComplete.Subscribe
	(
		[this](std::string Anim) { OnAbilityMontageCompleted(Anim); }
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
	if (isCollidorActivated && currentCollidorTime <= targetCollidorTime)
	{
		currentCollidorTime += deltaTime;
	}
	else
	{
		if (abilityCollidor && currentCollidorTime > targetCollidorTime)
		{
			abilityCollidor->Destroy();
			abilityCollidor = nullptr;
		}


		currentCollidorTime = 0.0f;
		isCollidorActivated = false;

	}

	if (owner && abilityCollidor)
	{
		float halfX = abilityCollidor->BoxSize.x * 0.5f;
		float halfY = abilityCollidor->BoxSize.y * 0.5f;
		abilityCollidor->Box.min = { owner->GetPosition().x - halfX + (abilInfo.collidorOffset->x * owner->GetCharacterDirection()), owner->GetPosition().y - halfY + abilInfo.collidorOffset->y };
		abilityCollidor->Box.max = { owner->GetPosition().x + halfX + (abilInfo.collidorOffset->x * owner->GetCharacterDirection()), owner->GetPosition().y + halfY + abilInfo.collidorOffset->y };
	}
}

// Make 3 child classes light heavy and dash ability so logic is simpler...core logic resides here...
void Ability::Activate()
{
	if (!isOnCooldown)
	{
		// Change the collidor appearance functionality so its time of appearance is in its config and is loaded...also make sure it is not set to true from the start we can have abilities that spawn
		// collidor box a bit late like a heavy attack
		isOnCooldown = !isOnCooldown;
		isCollidorActivated = true;
		isAbilityActivated = true;

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
			
			std::cout << "Spawning collidor for damage: " << totalDamage << std::endl;

			abilityCollidor = SpawnActor<CollisionComponent>(owner, true, totalDamage);

			//ability collision box size and offset should be saved with ability info so we dont have to hardcode it in this function.... also things like activation time and stuff like that
			abilityCollidor->BoxSize = abilInfo.collidorSize.value_or(glm::vec2(0.0f));
			float halfX = abilityCollidor->BoxSize.x * 0.5f;
			float halfY = abilityCollidor->BoxSize.y * 0.5f;
			abilityCollidor->Box.min = { owner->GetPosition().x - halfX + (abilInfo.collidorOffset->x * owner->GetCharacterDirection()), owner->GetPosition().y - halfY + abilInfo.collidorOffset->y };
			abilityCollidor->Box.max = { owner->GetPosition().x + halfX + (abilInfo.collidorOffset->x * owner->GetCharacterDirection()), owner->GetPosition().y + halfY + abilInfo.collidorOffset->y};
		}
	}
	
}

void Ability::OnAbilityMontageCompleted(std::string Anim)
{
	if (Anim == tag)
	{
		isAbilityActivated = false;
	}
}
