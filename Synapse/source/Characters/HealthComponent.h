#pragma once
#include <algorithm>



class HealthComponent
{

public:

	HealthComponent();


	void TakeDamage(float Damage) 
	{
		SetHealth(std::max(health - Damage, 0.0f));
	};

	void SetHealth(float healthValue) 
	{
		health = healthValue;
	};

	float GetHealth()
	{
		return health;
	};


private:

	float health = 100;

};

