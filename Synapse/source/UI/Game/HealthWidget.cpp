#include "../../Characters/Player.h"
#include "../../Game/Game.h"
#include "../../Game/Session.h"
#include "HealthWidget.h"
#include <iostream>

void HealthWidget::Init()
{
	SetAnchor(AnchorPoint::TopLeft);
	SetSize({ 600.0f, 85.0f });
	SetOffset({ 20.0f, 20.0f });
	widgetSprite.Init("Assets/UI/HealthBar.png");
	SetZOrder(1);

	HealthBar = SpawnActor<Widget>();
	HealthBar->SetAnchor(AnchorPoint::TopLeft);
	HealthBar->SetSize({ 600.0f, 40.0f });
	HealthBar->SetOffset({ 20.0f, 20.0f });
	HealthBar->SetColor({0.49f, 0.255f, 0.251f, 1.0f});
	HealthBar->SetZOrder(0);

	ArmorBar = SpawnActor<Widget>();
	ArmorBar->SetAnchor(AnchorPoint::TopLeft);
	ArmorBar->SetSize({ 600.0f, 40.0f });
	ArmorBar->SetOffset({ 20.0f, 60.0f });
	ArmorBar->SetColor({ 0.145f, 0.294f, 0.396f, 1.0f });
	ArmorBar->SetZOrder(0);


	Game::GetGame()->GetCurrentSession()->GetActivePlayer()->GetHealthComponent().onHealthChanged.Subscribe
	(
		[this](float BaseHealthPer, float ArmorHealthPer) { this->UpdateHealthBar(BaseHealthPer, ArmorHealthPer); }
	);
}

void HealthWidget::UpdateHealthBar(float BaseHealthPer, float ArmorHealthPer)
{
	// why 2 times this is firing investigate....
	std::cout << "The current health percentage is: " << BaseHealthPer << std::endl;

	ArmorBar->SetSize({ 600.0f * ArmorHealthPer, HealthBar->GetSize().y });
	HealthBar->SetSize({ 600.0f * BaseHealthPer, HealthBar->GetSize().y });
}
