#include "../../Game/Game.h"
#include "../../Game/Session.h"
#include "../../Game/WaveSpawner.h"
#include "../Base/TextWidget.h"
#include "WaveWidget.h"

void WaveWidget::Init()
{
	SetAnchor(AnchorPoint::TopRight);
	SetSize({ 400.0f, 250.0f });
	SetOffset({20.0f, 20.0f});
	widgetSprite.Init("Assets/UI/WaveInfo.png");
	SetZOrder(0);

	Font* font = Game::GetGame()->GetCurrentSession()->GetDefaultFont();

	// Wave Text
	WaveText = SpawnActor<TextWidget>(font, "WAVE 1");
	WaveText->SetColor({ 0.83f, 0.77f, 0.64f, 1.0f });
	WaveText->SetSize({ 30.0f, 30.0f });
	WaveText->SetOffset({ 160.0f, 80.0f });
	WaveText->SetAnchor(AnchorPoint::TopRight);
	WaveText->SetZOrder(1);

	
	Game::GetGame()->GetCurrentSession()->GetWaveSpawner()->OnWaveCompleted.Subscribe
	(
		[this](int waveCount) { WaveText->SetText("WAVE " + std::to_string(waveCount)); }
	);
	
}
