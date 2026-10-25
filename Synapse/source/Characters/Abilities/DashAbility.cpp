#include "../Character.h"
#include "DashAbility.h"


void DashAbility::Update(double deltaTime)
{
	Ability::Update(deltaTime);

	if (isAbilityActivated)
	{
		auto Owner = owner.lock();

		if (!Owner)
		{
			return;
		}

		Owner->UpdatePosition((dashMagnitude / dashIntervals), true);
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
		auto TargetAnimator = targetAnimator.lock();
		auto Owner = owner.lock();

		if (TargetAnimator)
		{
			float dashMultiplier = Owner->GetVitalsComponent().lock()->GetDashInfo().dashDistance.value_or(0.0f);
			glm::vec3 deltaPosition = Owner->GetPosition() - Owner->GetPreviousPosition();
			glm::vec3 dashDirection = { Owner->GetCharacterDirection(), 0.0, 0.0};
			if (deltaPosition != glm::vec3(0.0f))
			{
				dashDirection = deltaPosition / glm::length(deltaPosition);
			}

			dashMagnitude = dashDirection * dashMultiplier;
		}
	}
}
