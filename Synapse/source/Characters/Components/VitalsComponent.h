#pragma once

#include "../../Enums&Structs/GameTypes.h"
#include <string>

class Character;

class VitalsComponent 
{

public:

	VitalsComponent() {};

	VitalsComponent(Character* Owner);

	Delegate<> onDeath;
	Delegate<float> onVigorModified;
	Delegate<float> onPlatingModified;
	Delegate<AbilityVital> onAbilityModified;


private:

	Vitals ownerVitals = { {100.0f, 100.0f}, 1.0f, { 0.0f, 0.0f }, 0.0f, 0.0f, 0 , {"", 0.0f, 0.0f}, {"", 0.0f, 0.0f}, {"", 0.0f, 0.0f} };
	Character* owner = nullptr;


public:

	void TakeDamage(float Damage)
	{
		if (GetPlating() > 0.0f)
		{
			SetPlating(std::max(GetPlating() - Damage, 0.0f));
		}
		else
		{
			SetVigor(std::max(GetVigor() - Damage, 0.0f));
		}
	};

	void SetVitals(Vitals vitals) { ownerVitals = vitals; };
	void SetVigor(float vigorValue);
	void SetPlating(float platingValue);
	void ModifyVital(std::string category, std::string tag, float value, bool multiplier);

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

	float GetMomentum()
	{
		return ownerVitals.Momentum;
	};

	float GetRecovery()
	{
		return ownerVitals.Recovery;
	};

	float GetFocus()
	{
		return ownerVitals.Focus;
	};

	float GetInsight()
	{
		return ownerVitals.Insight;
	};

	AbilityVital GetLightAttackInfo()
	{
		return ownerVitals.LightAttack;
	};

	AbilityVital GetHeavyAttackInfo()
	{
		return ownerVitals.HeavyAttack;
	};

	AbilityVital GetDashInfo()
	{
		return ownerVitals.Dash;
	};
};