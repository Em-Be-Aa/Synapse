#include "../../Characters/Player.h"
#include "../../Game/Game.h"
#include "../../Game/Session.h"
#include "../../Templates/Templates.h"
#include "../../Text/Font.h"
#include "../Base/TextWidget.h"
#include "../Base/Widget.h"
#include "VitalsWidget.h"

void VitalsWidget::Init()
{
	Widget::Init();

	SetAnchor(AnchorPoint::LeftCenter);
	SetSize({ 10.0f, 300.0f });
	SetColor({ 0.0f, 0.0f, 0.0f, 0.0f });
	SetZOrder(0);


	Momentum = SpawnActor<AbilityWidget>("Assets/UI/MomemtumVital.png", this);
	Momentum->SetOffset({ 50.0f, 150.0f });
	Momentum->SetAnchor(AnchorPoint::Center);
	Momentum->SetZOrder(1);

	Focus = SpawnActor<AbilityWidget>("Assets/UI/FocusVital.png", this);
	Focus->SetOffset({ 50.0f, 50.0f });
	Focus->SetAnchor(AnchorPoint::Center);
	Focus->SetZOrder(1);

	Recovery = SpawnActor<AbilityWidget>("Assets/UI/RecoveryVital.png", this);
	Recovery->SetOffset({ 50.0f, -50.0f });
	Recovery->SetAnchor(AnchorPoint::Center);
	Recovery->SetZOrder(1);

	Insight = SpawnActor<AbilityWidget>("Assets/UI/InsightVital.png", this);
	Insight->SetOffset({ 50.0f, -150.0f });
	Insight->SetAnchor(AnchorPoint::Center);
	Insight->SetZOrder(1);



}

void VitalsWidget::Update(double dT)
{
	Widget::Update(dT);

	VitalsComponent& VC = Game::GetGame()->GetCurrentSession()->GetActivePlayer()->GetVitalsComponent();

	Momentum->GetText()->SetText("Momentum: " + std::to_string(static_cast<int>(std::round(VC.GetMomentum()))));
	Recovery->GetText()->SetText("Recovery: " + std::to_string(static_cast<int>(std::round(VC.GetRecovery() * 100.0f))) + "%");
	Focus->GetText()->SetText("Focus: " + std::to_string(static_cast<int>(std::round(VC.GetFocus() * 100.0f))) + "%");
	Insight->GetText()->SetText("Insight: " + std::to_string(static_cast<int>(std::round(VC.GetInsight() * 100.0f))) + "%");
	
}
