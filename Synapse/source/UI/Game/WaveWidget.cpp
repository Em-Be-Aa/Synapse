#include "../../Game/Game.h"
#include "../../Game/Session.h"
#include "../../Game/WaveSpawner.h"
#include "../Base/TextWidget.h"
#include "WaveWidget.h"

void WaveWidget::Init()
{
	SetAnchor(AnchorPoint::TopRight);
	SetSize({ 450.0f, 220.0f });
	SetOffset({20.0f, 20.0f});
	widgetSprite.Init("Assets/UI/WaveInfo.png");
	SetZOrder(0);

	Font* fontA = Game::GetGame()->GetCurrentSession()->GetLargeFont();
	Font* fontB = Game::GetGame()->GetCurrentSession()->GetDefaultFont();

	// Wave Text
	WaveText = SpawnActor<TextWidget>(fontA, "Wave 1", this);
	WaveText->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	WaveText->SetSize({ 30.0f, 30.0f });
	WaveText->SetOffset({ -10.0f, 10.0f });
	WaveText->SetAnchor(AnchorPoint::Center);
	WaveText->SetZOrder(1);

	WaveInfoText = SpawnActor<TextWidget>(fontB, "1/1", this);
	WaveInfoText->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	WaveInfoText->SetSize({ 15.0f, 15.0f });
	WaveInfoText->SetOffset({ -10.0f, -40.0f });
	WaveInfoText->SetAnchor(AnchorPoint::Center);
	WaveInfoText->SetZOrder(1);

	
	Game::GetGame()->GetCurrentSession()->GetWaveSpawner()->OnWaveCompleted.Subscribe
	(
		[this](int waveCount) { WaveText->SetText("WAVE " + std::to_string(waveCount)); }
	);
	
}

void WaveWidget::Update(double dT)
{
	WaveSpawner* WS = Game::GetGame()->GetCurrentSession()->GetWaveSpawner();
	WaveInfoText->SetText(std::to_string(WS->GetCurrentEnemyCount()) + "/" + std::to_string(WS->GetTotalEnemyCount()));

	Widget::Update(dT);
}
