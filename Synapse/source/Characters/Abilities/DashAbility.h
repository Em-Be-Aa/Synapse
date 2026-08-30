#pragma once

#include "Ability.h"
#include <string>

class DashAbility : public Ability 
{

public:
	
	using Ability::Ability;
	void Update(double deltaTime) override;
	void Activate() override;



};