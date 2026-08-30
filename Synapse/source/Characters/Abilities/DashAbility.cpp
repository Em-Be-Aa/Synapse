#include "../Character.h"
#include "DashAbility.h"


void DashAbility::Update(double deltaTime)
{
	Ability::Update(deltaTime);
}

void DashAbility::Activate()
{
	if (!isOnCooldown)
	{
		isOnCooldown = !isOnCooldown;
		isActivated = true;

		if (targetAnimator)
		{
			owner->Position = owner->Position + glm::vec3{ 1.0f, 0.0f, 0.0f };
		}
	}
}
