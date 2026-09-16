#include "../../Characters/Player.h"
#include "../../Game/Game.h"
#include "../../Game/Session.h"
#include "../../Templates/Templates.h"
#include "HealthWidget.h"
#include <iostream>

void HealthWidget::Init()
{
	Font* fontA = Game::GetGame()->GetCurrentSession()->GetSmallFont();

	SetAnchor(AnchorPoint::BottomLeft);
	SetSize({ 500.0f, 100.0f });
	SetOffset({ 20.0f, 20.0f });
	widgetSprite.Init("Assets/UI/HealthBar.png");
	SetZOrder(1);

	VigorBar = SpawnActor<Widget>();
	VigorBar->SetAnchor(AnchorPoint::BottomLeft);
	VigorBar->SetSize({ 440.0f, 28.0f });
	VigorBar->SetOffset({ 75.0f, 35.0f });
	VigorBar->SetColor({ 0.929, 0.161, 0.116, 1.0f});
	VigorBar->SetZOrder(0);

	PlatingBar = SpawnActor<Widget>();
	PlatingBar->SetAnchor(AnchorPoint::BottomLeft);
	PlatingBar->SetSize({ 440.0f, 28.0f });
	PlatingBar->SetOffset({ 75.0f, 85.0f });
	PlatingBar->SetColor({ 0.135, 0.343, 0.904, 1.0f });
	PlatingBar->SetZOrder(0);


	VigorText = SpawnActor<TextWidget>(fontA, "100/100", this);
	VigorText->SetAnchor(AnchorPoint::Center);
	VigorText->SetOffset({ 30.0f, -25 });
	VigorText->SetColor({ 1, 1, 1, 1.0f });
	VigorText->SetZOrder(1);

	PlatingText = SpawnActor<TextWidget>(fontA, "50/50", this);
	PlatingText->SetAnchor(AnchorPoint::Center);
	PlatingText->SetOffset({ 30.0f, 25 });
	PlatingText->SetColor({ 1, 1, 1, 1.0f });
	PlatingText->SetZOrder(1);


	Game::GetGame()->GetCurrentSession()->GetActivePlayer()->GetVitalsComponent().onVigorModified.Subscribe
	(
		[this](float Vigor, float MaxVigor) { this->UpdateVigorBar(Vigor, MaxVigor);}
	);


	Game::GetGame()->GetCurrentSession()->GetActivePlayer()->GetVitalsComponent().onPlatingModified.Subscribe
	(
		[this](float Plating, float MaxPlating) { this->UpdatePlatingBar(Plating, MaxPlating); }
	);

}

void HealthWidget::UpdateVigorBar(float Vigor, float MaxVigor)
{

	std::cout << "this is health change: " << Vigor << "-----" << MaxVigor << std::endl;
	VigorBar->SetSize({ 440.0f * (Vigor/MaxVigor), VigorBar->GetSize().y });
	VigorText->SetText(std::to_string(static_cast<int>(Vigor)) + "/" + std::to_string(static_cast<int>(MaxVigor)));
}

void HealthWidget::UpdatePlatingBar(float Plating, float MaxPlating)
{

	PlatingBar->SetSize({ 440.0f * (Plating/MaxPlating), PlatingBar->GetSize().y });
	PlatingText->SetText(std::to_string(static_cast<int>(Plating)) + "/" + std::to_string(static_cast<int>(MaxPlating)));
}
