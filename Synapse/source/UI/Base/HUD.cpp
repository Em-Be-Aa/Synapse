#include "../Game/WaveWidget.h"
#include "HUD.h"

void HUD::Init()
{
	// Create widget and add widget related logic here
	SpawnActor<WaveWidget>();

}


void HUD::Update(double dT)
{
}

