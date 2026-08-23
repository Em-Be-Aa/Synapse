#include "../Game/CharacterHealthBar.h"
#include "../Game/HealthWidget.h"
#include "../Game/WaveWidget.h"
#include "HUD.h"

void HUD::Init()
{
	// Create widget and add widget related logic here
	SpawnActor<WaveWidget>();
	SpawnActor<HealthWidget>();

}


void HUD::Update(double dT)
{
}

