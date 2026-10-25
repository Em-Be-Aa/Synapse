#include "../Character.h"
#include "AbilityComponent.h"
#include <string>


std::weak_ptr<Ability> AbilityComponent::GetAbility(std::string Tag)
{
	for (auto abil : abilities)
	{
		if (Tag == abil->tag)
		{
			return abil;
		}
	}
	return {};
}

void AbilityComponent::ActivateAbility(std::string Tag)
{
	// Multiple abilities can be active if passive abilities are introduced..so fix this later
	for (auto abil : abilities)
	{
		if (abil->IsAbilityActivated())
		{
			return;
		}
	
	}

	if (auto targetAbility = GetAbility(Tag).lock())
	{
		targetAbility->Activate();
	}
}
