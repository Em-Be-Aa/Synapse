#include "VitalsComponent.h"

VitalsComponent::VitalsComponent(Character* Owner)
{

}

void VitalsComponent::SetVigor(float vigorValue, bool modify)
{
	if (modify)
	{
		ownerVitals.Vigor.current = ownerVitals.Vigor.current + vigorValue;
	}
	else
	{
		ownerVitals.Vigor.current = vigorValue;
	}

	onVigorChanged.Broadcast( GetVigor() / GetMaxVigor() );

	if (GetVigor() <= 0.0f)
	{
		onDeath.Broadcast();
	}
}

void VitalsComponent::SetPlating(float platingValue, bool modify)
{
	if (modify)
	{
		ownerVitals.Plating.current = ownerVitals.Plating.current + platingValue;
	}
	else
	{
		ownerVitals.Plating.current = platingValue;
	}

	onPlatingChanged.Broadcast( GetPlating() / GetMaxPlating() );
}

void VitalsComponent::SetMomentum(float moementumValue, bool modify)
{
	if (modify)
	{
		ownerVitals.Momentum = ownerVitals.Momentum + moementumValue;
	}
	else
	{
		ownerVitals.Momentum = moementumValue;
	}

}

void VitalsComponent::SetFocus(float focusValue, bool modify)
{
	if (modify)
	{
		ownerVitals.Focus = ownerVitals.Focus + focusValue;
	}
	else
	{
		ownerVitals.Focus = focusValue;
	}

}

void VitalsComponent::SetRecovery(float recoveryValue, bool modify)
{
	if (modify)
	{
		ownerVitals.Recovery = ownerVitals.Recovery + recoveryValue;
	}
	else
	{
		ownerVitals.Recovery = recoveryValue;
	}

}

void VitalsComponent::SetInsight(float insightValue, bool modify)
{
	if (modify)
	{
		ownerVitals.Insight = ownerVitals.Insight + insightValue;
	}
	else
	{
		ownerVitals.Insight = insightValue;
	}

}

