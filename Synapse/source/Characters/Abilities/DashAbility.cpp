#include "../Character.h"
#include "DashAbility.h"


void DashAbility::Update(double deltaTime)
{
	Ability::Update(deltaTime);

	if (isAbilityActivated)
	{
		owner->UpdatePosition((dashMagnitude / dashIntervals), true);
		currentDashInterval++;

		if (currentDashInterval == dashIntervals)
		{
			currentDashInterval = 0.0f;
			isAbilityActivated = false;
		}
	}
}

void DashAbility::Activate()
{
	if (!isOnCooldown)
	{
		isOnCooldown = !isOnCooldown;
		isAbilityActivated = true;

		if (targetAnimator)
		{
			float dashMultiplier = owner->GetVitalsComponent().GetDashInfo().dashDistance.value_or(0.0f);
			glm::vec3 deltaPosition = owner->GetPosition() - owner->GetPreviousPosition();
			glm::vec3 dashDirection = { owner->GetCharacterDirection(), 0.0, 0.0};
			if (deltaPosition != glm::vec3(0.0f))
			{
				dashDirection = deltaPosition / glm::length(deltaPosition);
			}

			dashMagnitude = dashDirection * dashMultiplier;
		}
	}
}
