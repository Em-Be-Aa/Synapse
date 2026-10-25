
#include "../../Game/Game.h"
#include "../../Game/Session.h"
#include "../../Game/WaveSpawner.h"
#include "../../Managers/CardManager.h"
#include "../../Window/Window.h"
#include "../Game/AbilitiesWidget.h"
#include "../Game/HealthWidget.h"
#include "../Game/VitalsWidget.h"
#include "../Game/WaveWidget.h"
#include "HUD.h"

void HUD::Init()
{
	// Create widget and add widget related logic here
	SpawnActor<WaveWidget>();
	SpawnActor<HealthWidget>();
	SpawnActor<VitalsWidget>();
	SpawnActor<AbilitiesWidget>();
	
	Game::GetGame()->GetCurrentSession().lock()->GetWaveSpawner().lock()->OnWaveCompleted.Subscribe
	(
		[this](int waveNumber) {  ShowCardsWidget(true); }
	);

	CardManager::GetCardManager()->onCardSelected.Subscribe
	(
		[this]() { ShowCardsWidget(false); }
	);

}

void HUD::ShowCardsWidget(bool show)
{
	if (show)
	{
		Game::GetGame()->GetGameWindow().lock()->SetInputModeUI();
		CardManager::GetCardManager()->SetupCards();
	}
	else
	{
		Game::GetGame()->GetGameWindow().lock()->SetInputModeGame();
		auto WS = Game::GetGame()->GetCurrentSession().lock()->GetWaveSpawner().lock();
		WS->StartWave(WS->GetCurrentWaveCount());
	}
}


void HUD::Update(double dT)
{
}

