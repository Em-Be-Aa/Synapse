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

	Momentum = SpawnActor<AbilityWidget>("Assets/UI/MomemtumVital.png", std::dynamic_pointer_cast<Widget>(shared_from_this()));
	Momentum->SetOffset({ 50.0f, 150.0f });
	Momentum->SetAnchor(AnchorPoint::Center);
	Momentum->GetCooldown().lock()->SetVisibility(true);
	Momentum->GetText().lock()->SetVisibility(true);
	Momentum->GetText().lock()->SetColor({ 1, 1, 1, 0.75 });
	Momentum->SetZOrder(1);

	Focus = SpawnActor<AbilityWidget>("Assets/UI/FocusVital.png", std::dynamic_pointer_cast<Widget>(shared_from_this()));
	Focus->SetOffset({ 50.0f, 50.0f });
	Focus->SetAnchor(AnchorPoint::Center);
	Focus->GetCooldown().lock()->SetVisibility(true);
	Focus->GetText().lock()->SetVisibility(true);
	Focus->GetText().lock()->SetColor({ 1, 1, 1, 0.75 });
	Focus->SetZOrder(1);

	Recovery = SpawnActor<AbilityWidget>("Assets/UI/RecoveryVital.png", std::dynamic_pointer_cast<Widget>(shared_from_this()));
	Recovery->SetOffset({ 50.0f, -50.0f });
	Recovery->SetAnchor(AnchorPoint::Center); 
	Recovery->GetCooldown().lock()->SetVisibility(true);
	Recovery->GetText().lock()->SetVisibility(true);
	Recovery->GetText().lock()->SetColor({ 1, 1, 1, 0.75 });
	Recovery->SetZOrder(1);

	Insight = SpawnActor<AbilityWidget>("Assets/UI/InsightVital.png", std::dynamic_pointer_cast<Widget>(shared_from_this()));
	Insight->SetOffset({ 50.0f, -150.0f });
	Insight->SetAnchor(AnchorPoint::Center);
	Insight->GetCooldown().lock()->SetVisibility(true);
	Insight->GetText().lock()->SetVisibility(true);

	Insight->GetText().lock()->SetColor({ 1, 1, 1, 0.75 });
	Insight->SetZOrder(1);



}

void VitalsWidget::Update(double dT)
{
	Widget::Update(dT);

	auto VC = Game::GetGame()->GetCurrentSession().lock()->GetActivePlayer().lock()->GetVitalsComponent().lock();

	Momentum->GetText().lock()->SetText("+" + std::to_string(static_cast<int>(std::round(VC->GetMomentum() * 100.0f))) + "%");
	Recovery->GetText().lock()->SetText("+" + std::to_string(static_cast<int>(std::round(VC->GetRecovery() * 100.0f))) + "%");
	Focus->GetText().lock()->SetText("+" + std::to_string(static_cast<int>(std::round(VC->GetFocus() * 100.0f))) + "%");
	Insight->GetText().lock()->SetText("+" + std::to_string(static_cast<int>(std::round(VC->GetInsight() * 100.0f))) + "%");

}
