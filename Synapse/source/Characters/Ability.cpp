#include "Ability.h"


Ability::Ability(std::string abilTag, Animator* animator)
{
	tag = abilTag;
	targetAnimator = animator;
}

void Ability::Activate()
{
	if (targetAnimator)
	{
		targetAnimator->SetCurrentAnim(tag);
	}
}
