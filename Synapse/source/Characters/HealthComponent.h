#pragma once
#include "../Actor/Actor.h"
#include "../Templates/Templates.h"
#include <algorithm>


class HealthComponent
{

public:

	HealthComponent();

	HealthComponent(Actor* Owner);

	void TakeDamage(float Damage) 
	{
		if (isArmorEnabled && armorHealth > 0.0f)
		{
			SetArmorHealth(std::max(armorHealth - Damage, 0.0f));
		}
		else
		{
			SetBaseHealth(std::max(baseHealth - Damage, 0.0f));
		}
	};

	void SetBaseHealth(float healthValue);
	void SetArmorHealth(float healthValue);

	float GetBaseHealth()
	{
		return baseHealth;
	};

	float GetArmorHealth()
	{
		return armorHealth;
	};

	void EnableArmor(bool Enable) { isArmorEnabled = Enable; }

	Delegate<> onDeath;
	Delegate<float, float> onHealthChanged;

private:

	float baseHealth = 100;
	float armorHealth = 50;

	float maxBaseHealth = 100;
	float maxArmorHealth = 50;

	bool isArmorEnabled = false;

	Actor* owner = nullptr;
};

