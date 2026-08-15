#pragma once
#include "Ability.h"
#include <vector>

class Character;

class AbilityComponent
{

public:

	AbilityComponent(Character* C);

	Ability* GetAbility(std::string Tag);

	void AddAbility(std::string Tag);

	void ActivateAbility(std::string Tag);

	Character* GetOwner() 
	{
		return componentOwner;
	}

private:

	std::vector<Ability*> abilities;
	Character* componentOwner;


};

