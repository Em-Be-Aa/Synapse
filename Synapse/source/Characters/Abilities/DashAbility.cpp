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
			float dashMagnitude = owner->GetVitalsComponent().GetDashInfo().dashDistance.value_or(0.0f);
			glm::vec3 deltaPosition = owner->GetPosition() - owner->GetPreviousPosition();
			glm::vec3 dashDirection = { owner->GetCharacterDirection(), 0.0, 0.0};
			if (deltaPosition != glm::vec3(0.0f))
			{
				dashDirection = deltaPosition / glm::length(deltaPosition);
			}

			std::cout << " Modify Value: (" << (dashDirection * dashMagnitude).x << (dashDirection * dashMagnitude).y << std::endl;


			owner->UpdatePosition(dashDirection * dashMagnitude, true);
		}
	}
}
