#pragma once
#include "../Abilities/Ability.h"
#include <vector>

class Character;

class AbilityComponent
{

public:

	AbilityComponent(Character* C);

	Ability* GetAbility(std::string Tag);

	void ActivateAbility(std::string Tag);

	Character* GetOwner() 
	{
		return componentOwner;
	}

	std::vector<Ability*>& GetAbilities()
	{
		return abilities;
	}

private:

	std::vector<Ability*> abilities;
	Character* componentOwner;


};

