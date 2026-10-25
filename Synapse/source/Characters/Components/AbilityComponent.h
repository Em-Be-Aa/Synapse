#pragma once
#include "../Abilities/Ability.h"
#include <vector>

class Character;

class AbilityComponent : public Object
{

public:

	void Init() override {};
	void Update(double dT) override {};

	void ActivateAbility(std::string Tag);



private:

	std::vector<std::shared_ptr<Ability>> abilities;
	std::weak_ptr<Character> componentOwner;


public:

	void SetOwner(std::weak_ptr<Character> Owner)
	{
		componentOwner = Owner;
	}

	std::weak_ptr<Character> GetOwner()
	{
		return componentOwner;
	}

	std::vector<std::shared_ptr<Ability>>& GetAbilities()
	{
		return abilities;
	}

	std::weak_ptr<Ability> GetAbility(std::string Tag);

};

