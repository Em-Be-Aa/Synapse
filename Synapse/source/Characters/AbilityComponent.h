#pragma once
#include "Ability.h"
#include <vector>


class AbilityComponent
{

public:

	AbilityComponent();

	Ability* GetAbility(std::string Tag);

	void AddAbility(std::string Tag, Animator* targetAnimator);

	void ActivateAbility(std::string Tag);

private:

	std::vector<Ability*> abilities;

};

