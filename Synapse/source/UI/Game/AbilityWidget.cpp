#include "../../Characters/Player.h"
#include "../../Characters/Player.h"
#include "../../Game/Game.h"
#include "../../Game/Session.h"
#include "../../Templates/Templates.h"
#include "../../Text/Font.h"
#include "../Base/Widget.h"
#include "AbilityWidget.h"
#include <iostream>

void AbilityWidget::Init()
{
	Widget::Init();

	SetAnchor(AnchorPoint::BottomCenter);
	SetSize({ 250.0f, 300.0f });
	SetOffset({ 30.0f, 100.0f });
	SetColor({ 0.0f, 0.0f, 0.0f, 0.0f });
	SetZOrder(0);

	Font* fontA = Game::GetGame()->GetCurrentSession()->GetDefaultFont();

	LightBG = SpawnActor<Widget>("Assets/UI/AbilityBG.png");
	LightBG->SetSize({ 100.0f, 100.0f });
	LightBG->SetOffset({ -150.0f, 50.0f });
	LightBG->SetAnchor(AnchorPoint::BottomCenter);
	LightBG->SetZOrder(0);

	HeavyBG = SpawnActor<Widget>("Assets/UI/AbilityBG.png");
	HeavyBG->SetSize({ 100.0f, 100.0f });
	HeavyBG->SetOffset({ 0.0f, 50.0f });
	HeavyBG->SetAnchor(AnchorPoint::BottomCenter);
	HeavyBG->SetZOrder(0);

	DashBG = SpawnActor<Widget>("Assets/UI/AbilityBG.png");
	DashBG->SetSize({ 100.0f, 100.0f });
	DashBG->SetOffset({ 150.0f, 50.0f });
	DashBG->SetAnchor(AnchorPoint::BottomCenter);
	DashBG->SetZOrder(0);

	LightImage = SpawnActor<Widget>("Assets/UI/LightAttack.png");
	LightImage->SetSize({ 100.0f, 100.0f });
	LightImage->SetOffset({ -150.0f, 50.0f });
	LightImage->SetAnchor(AnchorPoint::BottomCenter);
	LightImage->SetZOrder(1);

	HeavyImage = SpawnActor<Widget>("Assets/UI/HeavyAttack.png");
	HeavyImage->SetSize({ 100.0f, 100.0f });
	HeavyImage->SetOffset({ 0.0f, 50.0f });
	HeavyImage->SetAnchor(AnchorPoint::BottomCenter);
	HeavyImage->SetZOrder(1);

	DashImage = SpawnActor<Widget>("Assets/UI/DashAbility.png");
	DashImage->SetSize({ 100.0f, 100.0f });
	DashImage->SetOffset({ 150.0f, 50.0f });
	DashImage->SetAnchor(AnchorPoint::BottomCenter);
	DashImage->SetZOrder(1);


	LightCooldown = SpawnActor<Widget>();
	LightCooldown->SetColor({ 0.2, 0.2, 0.2, 0.4f });
	LightCooldown->SetSize({ 100.0f, 100.0f });
	LightCooldown->SetOffset({ -150.0f, 50.0f });
	LightCooldown->SetAnchor(AnchorPoint::BottomCenter);
	LightCooldown->SetZOrder(2);

	HeavyCooldown = SpawnActor<Widget>();
	HeavyCooldown->SetColor({ 0.2, 0.2, 0.2, 0.4f });
	HeavyCooldown->SetSize({ 100.0f, 100.0f });
	HeavyCooldown->SetOffset({ 0.0f, 50.0f });
	HeavyCooldown->SetAnchor(AnchorPoint::BottomCenter);
	HeavyCooldown->SetZOrder(2);

	DashCooldown = SpawnActor<Widget>();
	DashCooldown->SetColor({ 0.2, 0.2, 0.2, 0.4f });
	DashCooldown->SetSize({ 100.0f, 100.0f });
	DashCooldown->SetOffset({ 150.0f, 50.0f });
	DashCooldown->SetAnchor(AnchorPoint::BottomCenter);
	DashCooldown->SetZOrder(2);


}

void AbilityWidget::Update(double dT)
{
	Widget::Update(dT);

	float LightAttackCooldown = Game::GetGame()->GetCurrentSession()->GetActivePlayer()->GetAbilityComponent().GetAbility("LIGHT ATTACK")->GetCurrentCooldownPerc();
	LightCooldown->SetSize({ 100 * LightAttackCooldown, LightCooldown->GetSize().y });

	float HeavyAttackCooldown = Game::GetGame()->GetCurrentSession()->GetActivePlayer()->GetAbilityComponent().GetAbility("HEAVY ATTACK")->GetCurrentCooldownPerc();
	HeavyCooldown->SetSize({ 100 * HeavyAttackCooldown, HeavyCooldown->GetSize().y });

	float DashAbilityCooldown = Game::GetGame()->GetCurrentSession()->GetActivePlayer()->GetAbilityComponent().GetAbility("DASH")->GetCurrentCooldownPerc();
	DashCooldown->SetSize({ 100 * DashAbilityCooldown, DashCooldown->GetSize().y });

}
