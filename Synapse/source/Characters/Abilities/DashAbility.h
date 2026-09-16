#pragma once

#include "Ability.h"
#include <string>

class DashAbility : public Ability 
{

public:
	
	using Ability::Ability;
	void Update(double deltaTime) override;
	void Activate() override;

private:

	glm::vec3 dashMagnitude;
	float dashIntervals = 10.0f;
	float currentDashInterval = 0.0f;
};