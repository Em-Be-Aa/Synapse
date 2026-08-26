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

	VigorBar = SpawnActor<Widget>();
	VigorBar->SetAnchor(AnchorPoint::TopLeft);
	VigorBar->SetSize({ 600.0f, 40.0f });
	VigorBar->SetOffset({ 20.0f, 20.0f });
	VigorBar->SetColor({0.49f, 0.255f, 0.251f, 1.0f});
	VigorBar->SetZOrder(0);

	PlatingBar = SpawnActor<Widget>();
	PlatingBar->SetAnchor(AnchorPoint::TopLeft);
	PlatingBar->SetSize({ 600.0f, 40.0f });
	PlatingBar->SetOffset({ 20.0f, 60.0f });
	PlatingBar->SetColor({ 0.145f, 0.294f, 0.396f, 1.0f });
	PlatingBar->SetZOrder(0);


	Game::GetGame()->GetCurrentSession()->GetActivePlayer()->GetVitalsComponent().onVigorChanged.Subscribe
	(
		[this](float VigorPer) { this->UpdateVigorBar(VigorPer);}
	);


	Game::GetGame()->GetCurrentSession()->GetActivePlayer()->GetVitalsComponent().onPlatingChanged.Subscribe
	(
		[this](float PlatingPer) { this->UpdatePlatingBar(PlatingPer); }
	);

}

void HealthWidget::UpdateVigorBar(float VigorPer)
{
	VigorBar->SetSize({ 600.0f * VigorPer, VigorBar->GetSize().y });
}

void HealthWidget::UpdatePlatingBar(float PlatingPer)
{
	PlatingBar->SetSize({ 600.0f * PlatingPer, PlatingBar->GetSize().y });
}
