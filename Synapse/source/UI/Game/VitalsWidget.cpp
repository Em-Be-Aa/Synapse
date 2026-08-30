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

	SetAnchor(AnchorPoint::TopLeft);
	SetSize({ 250.0f, 300.0f });
	SetOffset({ 30.0f, 100.0f });
	SetColor({ 0.0f, 0.0f, 0.0f, 0.0f });
	SetZOrder(0);

	Font* fontA = Game::GetGame()->GetCurrentSession()->GetDefaultFont();

	VigorBG = SpawnActor<Widget>("Assets/UI/VitalBackground_V2.png");
	VigorBG->SetSize({ 300.0f, 50.0f });
	VigorBG->SetOffset({ 20.0f, 210.0f });
	VigorBG->SetAnchor(AnchorPoint::TopLeft);
	VigorBG->SetZOrder(1);

	PlatingBG = SpawnActor<Widget>("Assets/UI/VitalBackground_V2.png");
	PlatingBG->SetSize({ 300.0f, 50.0f });
	PlatingBG->SetOffset({ 20.0f, 270.0f });
	PlatingBG->SetAnchor(AnchorPoint::TopLeft);
	PlatingBG->SetZOrder(1);

	MomentumBG = SpawnActor<Widget>("Assets/UI/VitalBackground_V2.png");
	MomentumBG->SetSize({ 300.0f, 50.0f });
	MomentumBG->SetOffset({ 20.0f, 330.0f });
	MomentumBG->SetAnchor(AnchorPoint::TopLeft);
	MomentumBG->SetZOrder(1);

	FocusBG = SpawnActor<Widget>("Assets/UI/VitalBackground_V2.png");
	FocusBG->SetSize({ 300.0f, 50.0f });
	FocusBG->SetOffset({ 20.0f, 390.0f });
	FocusBG->SetAnchor(AnchorPoint::TopLeft);
	FocusBG->SetZOrder(1);

	RecoveryBG = SpawnActor<Widget>("Assets/UI/VitalBackground_V2.png");
	RecoveryBG->SetSize({ 300.0f, 50.0f });
	RecoveryBG->SetOffset({ 20.0f, 450.0f });
	RecoveryBG->SetAnchor(AnchorPoint::TopLeft);
	RecoveryBG->SetZOrder(1);

	InsightBG = SpawnActor<Widget>("Assets/UI/VitalBackground_V2.png");
	InsightBG->SetSize({ 300.0f, 50.0f });
	InsightBG->SetOffset({ 20.0f, 510.0f });
	InsightBG->SetAnchor(AnchorPoint::TopLeft);
	InsightBG->SetZOrder(1);




	VigorText = SpawnActor<TextWidget>(fontA, "Vigor : 100");
	VigorText->SetColor({ 0.83f, 0.77f, 0.64f, 1.0f });
	VigorText->SetSize({ 30.0f, 30.0f });
	VigorText->SetOffset({ 50.0f, 232.0f });
	VigorText->SetAnchor(AnchorPoint::TopLeft);
	VigorText->SetZOrder(2);

	PlatingText = SpawnActor<TextWidget>(fontA, "Plating : 50");
	PlatingText->SetColor({ 0.83f, 0.77f, 0.64f, 1.0f });
	PlatingText->SetSize({ 30.0f, 30.0f });
	PlatingText->SetOffset({ 50.0f, 292.0f });
	PlatingText->SetAnchor(AnchorPoint::TopLeft);
	PlatingText->SetZOrder(2);

	MomentumText = SpawnActor<TextWidget>(fontA, "Momentum : 1");
	MomentumText->SetColor({ 0.83f, 0.77f, 0.64f, 1.0f });
	MomentumText->SetSize({ 30.0f, 30.0f });
	MomentumText->SetOffset({ 50.0f, 352.0f });
	MomentumText->SetAnchor(AnchorPoint::TopLeft);
	MomentumText->SetZOrder(2);

	FocusText = SpawnActor<TextWidget>(fontA, "Focus : 0");
	FocusText->SetColor({ 0.83f, 0.77f, 0.64f, 1.0f });
	FocusText->SetSize({ 30.0f, 30.0f });
	FocusText->SetOffset({ 50.0f, 412.0f });
	FocusText->SetAnchor(AnchorPoint::TopLeft);
	FocusText->SetZOrder(2);

	RecoveryText = SpawnActor<TextWidget>(fontA, "Recovery : 0");
	RecoveryText->SetColor({ 0.83f, 0.77f, 0.64f, 1.0f });
	RecoveryText->SetSize({ 30.0f, 30.0f });
	RecoveryText->SetOffset({ 50.0f, 472.0f });
	RecoveryText->SetAnchor(AnchorPoint::TopLeft);
	RecoveryText->SetZOrder(2);

	InsightText = SpawnActor<TextWidget>(fontA, "Insight : 0");
	InsightText->SetColor({ 0.83f, 0.77f, 0.64f, 1.0f });
	InsightText->SetSize({ 30.0f, 30.0f });
	InsightText->SetOffset({ 50.0f, 532.0f });
	InsightText->SetAnchor(AnchorPoint::TopLeft);
	InsightText->SetZOrder(2);

}

void VitalsWidget::Update(double dT)
{
	Widget::Update(dT);

	VitalsComponent& VC = Game::GetGame()->GetCurrentSession()->GetActivePlayer()->GetVitalsComponent();

	VigorText->SetText("Vigor: " + std::to_string(static_cast<int>(std::round(VC.GetMaxVigor()))));
	PlatingText->SetText("Plating: " + std::to_string(static_cast<int>(std::round(VC.GetMaxPlating()))));
	MomentumText->SetText("Momentum: " + std::to_string(static_cast<int>(std::round(VC.GetMomentum()))));

	RecoveryText->SetText("Recovery: " + std::to_string(static_cast<int>(std::round(VC.GetRecovery() * 100.0f))) + "%");
	FocusText->SetText("Focus: " + std::to_string(static_cast<int>(std::round(VC.GetFocus() * 100.0f))) + "%");
	InsightText->SetText("Insight: " + std::to_string(static_cast<int>(std::round(VC.GetInsight() * 100.0f))) + "%");

	
}
