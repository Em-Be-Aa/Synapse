#include "AbilityComponent.h"
#include "Character.h"
#include <string>

AbilityComponent::AbilityComponent(Character* C)
{
	componentOwner = C;
}


// We are assuming characters can have and use abilities....look into this if this is the right approach
void AbilityComponent::AddAbility(std::string Tag)
{
	std::unique_ptr<Ability> ability(new Ability(Tag, componentOwner->GetSpriteComponent().spriteAnimator));
	Ability* newAbility = ability.get();
	UpdateManager::GetUpdateManager().Register(std::move(ability));
	newAbility->Init();
	abilities.push_back(newAbility);
}


Ability* AbilityComponent::GetAbility(std::string Tag)
{
	for (auto abil : abilities)
	{
		if (Tag == abil->tag)
		{
			return abil;
		}
	}
	return nullptr;
}

void AbilityComponent::ActivateAbility(std::string Tag)
{
	// Multiple abilities can be active if passive abilities are introduced..so fix this later
	for (auto abil : abilities)
	{
		if (abil->GetCooldownStatus())
		{
			return;
		}
	
	}

	if (Ability* targetAbility = GetAbility(Tag))
	{
		targetAbility->Activate(componentOwner);
	}
}
