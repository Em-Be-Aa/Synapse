#include "HUD.h"
#include "TextWidget.h"

void HUD::Init()
{
	// Create widget and add widget related logic here
	SpawnActor<Widget>("Assets/Textures/HealthBar.png", glm::vec2{ 200.0f, 80.0f }, glm::vec2{0.04, 0.85} );
	SpawnActor<TextWidget>(defaultFont, "100/100", glm::vec4{ 0.34f, 0.08f, 0.63f, 0.8f }, glm::vec2{ 200.0f, 100.0f }, glm::vec2{ 0.04, 0.82 });

}


void HUD::Update(double dT)
{
}

