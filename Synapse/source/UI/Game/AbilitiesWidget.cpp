#include "../../Characters/Player.h"
#include "../../Game/Game.h"
#include "../../Game/Session.h"
#include "../../Templates/Templates.h"
#include "../../Text/Font.h"
#include "../Base/TextWidget.h"
#include "../Base/Widget.h"
#include "AbilitiesWidget.h"
#include <format>
#include <iostream>

void AbilitiesWidget::Init()
{
	Widget::Init();

	SetAnchor(AnchorPoint::BottomCenter);
	SetSize({ 250.0f, 300.0f });
	SetOffset({ 30.0f, 100.0f });
	SetColor({ 0.0f, 0.0f, 0.0f, 0.0f });
	SetZOrder(0);

	Font* fontA = Game::GetGame()->GetCurrentSession()->GetDefaultFont();

	Light = SpawnActor<AbilityWidget>("Assets/UI/LightAttack.png");
	Light->SetSize({ 80.0f, 80.0f });
	Light->SetOffset({ -100.0f, 25.0f });
	Light->GetCooldown()->SetVisibility(true);
	Light->SetAnchor(AnchorPoint::BottomCenter);
	Light->SetZOrder(0);

	Heavy = SpawnActor<AbilityWidget>("Assets/UI/HeavyAttack.png");
	Heavy->SetSize({ 80.0f, 80.0f });
	Heavy->SetOffset({ 0.0f, 25.0f });
	Heavy->GetCooldown()->SetVisibility(true);
	Heavy->SetAnchor(AnchorPoint::BottomCenter);
	Heavy->SetZOrder(0);

	Dash = SpawnActor<AbilityWidget>("Assets/UI/DashAbility.png");
	Dash->SetSize({ 80.0f, 80.0f });
	Dash->SetOffset({ 100.0f, 25.0f });
	Dash->GetCooldown()->SetVisibility(true);
	Dash->SetAnchor(AnchorPoint::BottomCenter);
	Dash->SetZOrder(0);


}

void AbilitiesWidget::Update(double dT)
{
	Widget::Update(dT);

	float LightAttackCooldown = Game::GetGame()->GetCurrentSession()->GetActivePlayer()->GetAbilityComponent().GetAbility("LIGHT ATTACK")->GetCurrentCooldown();
	if (LightAttackCooldown > 0.0f)
	{
		Light->GetCooldown()->SetSize({70.0f, 70.0f});
		std::string cooldownStr = std::format("{:.1f}", LightAttackCooldown);
		Light->GetText()->SetText(cooldownStr);
		Light->GetText()->SetVisibility(true);
	}
	else
	{
		Light->GetCooldown()->SetSize({ 0, 0 });
		Light->GetText()->SetVisibility(false);
	}


	float HeavyAttackCooldown = Game::GetGame()->GetCurrentSession()->GetActivePlayer()->GetAbilityComponent().GetAbility("HEAVY ATTACK")->GetCurrentCooldown();
	if (HeavyAttackCooldown > 0.0f)
	{
		Heavy->GetCooldown()->SetSize({ 70.0f, 70.0f });
		std::string cooldownStr = std::format("{:.1f}", HeavyAttackCooldown);
		Heavy->GetText()->SetText(cooldownStr);
		Heavy->GetText()->SetVisibility(true);
	}
	else
	{
		Heavy->GetCooldown()->SetSize({ 0, 0 });
		Heavy->GetText()->SetVisibility(false);
	}

	float DashAbilityCooldown = Game::GetGame()->GetCurrentSession()->GetActivePlayer()->GetAbilityComponent().GetAbility("DASH")->GetCurrentCooldown();
	if (DashAbilityCooldown > 0.0f)
	{
		Dash->GetCooldown()->SetSize({ 70.0f, 70.0f });
		std::string cooldownStr = std::format("{:.1f}", DashAbilityCooldown);
		Dash->GetText()->SetText(cooldownStr);
		Dash->GetText()->SetVisibility(true);
	}
	else
	{
		Dash->GetCooldown()->SetSize({ 0, 0 });
		Dash->GetText()->SetVisibility(false);
	};

}
