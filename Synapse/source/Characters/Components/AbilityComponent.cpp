#include "../Character.h"
#include "AbilityComponent.h"
#include <string>

AbilityComponent::AbilityComponent(Character* C)
{
	componentOwner = C;
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
		targetAbility->Activate();
	}
}
