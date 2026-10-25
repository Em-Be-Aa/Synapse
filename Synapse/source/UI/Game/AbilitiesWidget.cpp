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

	// so many locks usage without checks just because i know that session or object will be alive...research how to make this better
	auto fontA = Game::GetGame()->GetCurrentSession().lock()->GetDefaultFont().lock();

	Light = SpawnActor<AbilityWidget>("Assets/UI/LightAttack.png");
	Light->SetSize({ 80.0f, 80.0f });
	Light->SetOffset({ -100.0f, 25.0f });
	Light->GetCooldown().lock()->SetVisibility(true);
	Light->SetAnchor(AnchorPoint::BottomCenter);
	Light->SetZOrder(0);

	Heavy = SpawnActor<AbilityWidget>("Assets/UI/HeavyAttack.png");
	Heavy->SetSize({ 80.0f, 80.0f });
	Heavy->SetOffset({ 0.0f, 25.0f });
	Heavy->GetCooldown().lock()->SetVisibility(true);
	Heavy->SetAnchor(AnchorPoint::BottomCenter);
	Heavy->SetZOrder(0);

	Dash = SpawnActor<AbilityWidget>("Assets/UI/DashAbility.png");
	Dash->SetSize({ 80.0f, 80.0f });
	Dash->SetOffset({ 100.0f, 25.0f });
	Dash->GetCooldown().lock()->SetVisibility(true);
	Dash->SetAnchor(AnchorPoint::BottomCenter);
	Dash->SetZOrder(0);


}

void AbilitiesWidget::Update(double dT)
{
	Widget::Update(dT);

	float LightAttackCooldown = Game::GetGame()->GetCurrentSession().lock()->GetActivePlayer().lock()->GetAbilityComponent().lock()->GetAbility("LIGHT ATTACK").lock()->GetCurrentCooldown();
	if (LightAttackCooldown > 0.0f)
	{
		Light->GetCooldown().lock()->SetSize({70.0f, 70.0f});
		std::string cooldownStr = std::format("{:.1f}", LightAttackCooldown);
		Light->GetText().lock()->SetText(cooldownStr);
		Light->GetText().lock()->SetVisibility(true);
	}
	else
	{
		Light->GetCooldown().lock()->SetSize({0, 0});
		Light->GetText().lock()->SetVisibility(false);
	}


	float HeavyAttackCooldown = Game::GetGame()->GetCurrentSession().lock()->GetActivePlayer().lock()->GetAbilityComponent().lock()->GetAbility("HEAVY ATTACK").lock()->GetCurrentCooldown();
	if (HeavyAttackCooldown > 0.0f)
	{
		Heavy->GetCooldown().lock()->SetSize({70.0f, 70.0f});
		std::string cooldownStr = std::format("{:.1f}", HeavyAttackCooldown);
		Heavy->GetText().lock()->SetText(cooldownStr);
		Heavy->GetText().lock()->SetVisibility(true);
	}
	else
	{
		Heavy->GetCooldown().lock()->SetSize({0, 0});
		Heavy->GetText().lock()->SetVisibility(false);
	}

	float DashAbilityCooldown = Game::GetGame()->GetCurrentSession().lock()->GetActivePlayer().lock()->GetAbilityComponent().lock()->GetAbility("DASH").lock()->GetCurrentCooldown();
	if (DashAbilityCooldown > 0.0f)
	{
		Dash->GetCooldown().lock()->SetSize({70.0f, 70.0f});
		std::string cooldownStr = std::format("{:.1f}", DashAbilityCooldown);
		Dash->GetText().lock()->SetText(cooldownStr);
		Dash->GetText().lock()->SetVisibility(true);
	}
	else
	{
		Dash->GetCooldown().lock()->SetSize({ 0, 0 });
		Dash->GetText().lock()->SetVisibility(false);
	};

}
