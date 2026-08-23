#include "HealthComponent.h"

HealthComponent::HealthComponent()
{

}

HealthComponent::HealthComponent(Actor* Owner)
{
	owner = Owner;
}

void HealthComponent::SetArmorHealth(float healthValue)
{
	if (armorHealth == healthValue)
	{
		return;
	}

	armorHealth = healthValue;

	onHealthChanged.Broadcast(baseHealth / maxBaseHealth, armorHealth / maxArmorHealth);
}

void HealthComponent::SetBaseHealth(float healthValue)
{
	if (baseHealth == healthValue)
	{
		return;
	}

	baseHealth = healthValue;

	onHealthChanged.Broadcast(baseHealth/maxBaseHealth, armorHealth/maxArmorHealth);

	if (baseHealth <= 0.0f)
	{
		onDeath.Broadcast();
	}
}
