#include "../Abilities/Ability.h"
#include "AbilityComponent.h"
#include "VitalsComponent.h"
#include <iostream>

VitalsComponent::VitalsComponent(Character* Owner)
{

}

void VitalsComponent::SetVigor(float vigorValue)
{

	ownerVitals.Vigor.current = vigorValue;
	onVigorModified.Broadcast( GetVigor() / GetMaxVigor() );

	if (GetVigor() <= 0.0f)
	{
		onDeath.Broadcast();
	}
}

void VitalsComponent::SetPlating(float platingValue)
{
	ownerVitals.Plating.current = platingValue;
	onPlatingModified.Broadcast( GetPlating() / GetMaxPlating() );
}


void VitalsComponent::ModifyVital(std::string category, std::string tag, float value, bool multiplier)
{
	std::cout << "[VitalsComponent] Current Stats -> " << value << std::endl;

	auto ApplyStat = [value, multiplier](auto& statValue)
		{
			statValue = multiplier ? (1.0f + value) * statValue : value + statValue;
		};

	auto ApplyResource = [value, multiplier](auto& resourceValue)
		{
			resourceValue.current = multiplier ? (resourceValue.max * value) + resourceValue.current : value + resourceValue.current;
			resourceValue.max = multiplier ? (1.0f + value) * resourceValue.max : value + resourceValue.max;
		};


	if (tag == "VIGOR")
	{
		ApplyResource(ownerVitals.Vigor);
		onVigorModified.Broadcast(GetVigor() / GetMaxVigor());
	}
	else if (tag == "PLATING")
	{
		ApplyResource(ownerVitals.Plating); 
		onPlatingModified.Broadcast(GetPlating() / GetMaxPlating());
	}
	else if (tag == "MOMENTUM")
	{
		ApplyStat(ownerVitals.Momentum);
	}
	else if (tag == "FOCUS")
	{
		ApplyStat(ownerVitals.Focus);
	}
	else if (tag == "RECOVERY")
	{
		ApplyStat(ownerVitals.Recovery);
	}
	else if (tag == "INSIGHT")
	{
		ApplyStat(ownerVitals.Insight);
	}
	else if (category == "LIGHT ATTACK")
	{
		if (tag == "DAMAGE")
		{
			ApplyStat(ownerVitals.LightAttack.abilityDamage);
		}
		else if(tag == "COOLDOWN")
		{

			ApplyStat(ownerVitals.LightAttack.abilityCooldown);
		}
		onAbilityModified.Broadcast(ownerVitals.LightAttack);
	}
	else if (category == "HEAVY ATTACK")
	{
		if (tag == "DAMAGE")
		{
			ApplyStat(ownerVitals.HeavyAttack.abilityDamage);
		}
		else if (tag == "COOLDOWN")
		{

			ApplyStat(ownerVitals.HeavyAttack.abilityCooldown);
		}
		onAbilityModified.Broadcast(ownerVitals.HeavyAttack);
	}
	else if (category == "DASH")
	{
		if (tag == "DAMAGE")
		{
			ApplyStat(ownerVitals.Dash.abilityDamage);
		}
		else if (tag == "COOLDOWN")
		{

			ApplyStat(ownerVitals.Dash.abilityCooldown);
		}
		else if (tag == "DISTANCE")
		{

			ApplyStat(*ownerVitals.Dash.dashDistance);
		}
		onAbilityModified.Broadcast(ownerVitals.Dash);
	}




	std::cout << "[VitalsComponent] Current Stats -> "
		<< "Vigor(Max): " << ownerVitals.Vigor.max << " | "
		<< "Plating(Max): " << ownerVitals.Plating.max << " | "
		<< "Momentum: " << ownerVitals.Momentum << " | "
		<< "Focus: " << ownerVitals.Focus << " | "
		<< "Recovery: " << ownerVitals.Recovery << " | "
		<< "Insight: " << ownerVitals.Insight << " | "
		<< "Light Damage: " << ownerVitals.LightAttack.abilityDamage << " | "
		<< "Light Cooldown: " << ownerVitals.LightAttack.abilityCooldown << " | "
		<< "Heavy Damage: " << ownerVitals.HeavyAttack.abilityDamage << " | "
		<< "Heavy Cooldown: " << ownerVitals.HeavyAttack.abilityCooldown << " | "
		<< "Dash Damage: " << ownerVitals.Dash.abilityDamage << " | "
		<< "Dash Cooldown: " << ownerVitals.Dash.abilityCooldown << " | "
		<< "Dash Distance: " << ownerVitals.Dash.dashDistance.value_or(0.0f) << " | "
		<< std::endl;
}

