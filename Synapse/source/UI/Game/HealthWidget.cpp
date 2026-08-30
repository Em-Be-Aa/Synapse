#include "../../Characters/Player.h"
#include "../../Game/Game.h"
#include "../../Game/Session.h"
#include "../../Templates/Templates.h"
#include "HealthWidget.h"
#include <iostream>

void HealthWidget::Init()
{
	SetAnchor(AnchorPoint::TopLeft);
	SetSize({ 600.0f, 185.0f });
	SetOffset({ 20.0f, 20.0f });
	widgetSprite.Init("Assets/UI/HealthBar_V2.png");
	SetZOrder(1);

	VigorBar = SpawnActor<Widget>();
	VigorBar->SetAnchor(AnchorPoint::TopLeft);
	VigorBar->SetSize({ 477.0f, 50.0f });
	VigorBar->SetOffset({ 107.0f, 35.0f });
	VigorBar->SetColor({ 0.361, 0.125, 0.145, 1.0f});
	VigorBar->SetZOrder(0);

	PlatingBar = SpawnActor<Widget>();
	PlatingBar->SetAnchor(AnchorPoint::TopLeft);
	PlatingBar->SetSize({ 477.0f, 50.0f });
	PlatingBar->SetOffset({ 107.0f, 140.0f });
	PlatingBar->SetColor({ 0.239, 0.275, 0.322, 1.0f });
	PlatingBar->SetZOrder(0);


	Game::GetGame()->GetCurrentSession()->GetActivePlayer()->GetVitalsComponent().onVigorModified.Subscribe
	(
		[this](float VigorPer) { this->UpdateVigorBar(VigorPer);}
	);


	Game::GetGame()->GetCurrentSession()->GetActivePlayer()->GetVitalsComponent().onPlatingModified.Subscribe
	(
		[this](float PlatingPer) { this->UpdatePlatingBar(PlatingPer); }
	);

}

void HealthWidget::UpdateVigorBar(float VigorPer)
{
	VigorBar->SetSize({ 477.0f * VigorPer, VigorBar->GetSize().y });
}

void HealthWidget::UpdatePlatingBar(float PlatingPer)
{
	PlatingBar->SetSize({ 477.0f * PlatingPer, PlatingBar->GetSize().y });
}
