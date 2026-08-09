#include "HealthComponent.h"

HealthComponent::HealthComponent()
{

}

HealthComponent::HealthComponent(Actor* Owner)
{
	owner = Owner;
}

void HealthComponent::SetHealth(float healthValue)
{
	health = healthValue;

	if (health <= 0.0f)
	{
		onDeath.Broadcast();
	}
}
