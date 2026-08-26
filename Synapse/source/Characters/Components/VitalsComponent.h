#pragma once

#include "../../Enums&Structs/GameTypes.h"
#include "../../Templates/Templates.h"

class Character;

class VitalsComponent 
{

public:

	VitalsComponent() {};

	VitalsComponent(Character* Owner);

	Delegate<> onDeath;
	Delegate<float> onVigorChanged;
	Delegate<float> onPlatingChanged;


private:

	Vitals ownerVitals = { {100.0f, 100.0f}, 1.0f, { 0.0f, 0.0f }, 0.0f, 0.0f, 0};
	Character* owner = nullptr;


public:

	void TakeDamage(float Damage)
	{
		if (GetPlating() > 0.0f)
		{
			SetPlating(std::max(GetPlating() - Damage, 0.0f), false);
		}
		else
		{
			SetVigor(std::max(GetVigor() - Damage, 0.0f), false);
		}
	};

	void SetVitals(Vitals vitals) { ownerVitals = vitals; };
	void SetVigor(float vigorValue, bool modify);
	void SetPlating(float platingValue, bool modify);
	void SetMomentum(float moementumValue, bool modify);
	void SetFocus(float focusValue, bool modify);
	void SetRecovery(float recoveryValue, bool modify);
	void SetInsight(float insightValue, bool modify);

	float GetVigor()
	{
		return ownerVitals.Vigor.current;
	};

	float GetPlating()
	{
		return ownerVitals.Plating.current;
	};

	float GetMaxVigor()
	{
		return ownerVitals.Vigor.max;
	};

	float GetMaxPlating()
	{
		return ownerVitals.Plating.max;
	};


};