#include "../../Characters/Player.h"
#include "../../Game/Game.h"
#include "../../Game/Session.h"
#include "../../Templates/Templates.h"
#include "HealthWidget.h"
#include <iostream>

void HealthWidget::Init()
{
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
