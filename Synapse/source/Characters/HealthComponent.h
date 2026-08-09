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
		SetHealth(std::max(health - Damage, 0.0f));
	};

	void SetHealth(float healthValue);

	float GetHealth()
	{
		return health;
	};

	Delegate<> onDeath;

private:

	float health = 100;
	Actor* owner = nullptr;
};

