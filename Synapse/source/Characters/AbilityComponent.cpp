#include "AbilityComponent.h"
#include <string>

AbilityComponent::AbilityComponent()
{

}

void AbilityComponent::AddAbility(std::string Tag, Animator* targetAnimator)
{
	Ability* newAbility = new Ability(Tag, targetAnimator);
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
	if (Ability* targetAbility = GetAbility(Tag))
	{
		targetAbility->Activate();
	}
}
