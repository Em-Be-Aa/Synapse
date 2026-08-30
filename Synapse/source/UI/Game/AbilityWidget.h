#pragma once

#include "../Base/Widget.h"

class TextWidget;

class AbilityWidget : public Widget
{

public:

	void Init() override;
	void Update(double dT) override;


private:

	Widget* LightBG;
	Widget* HeavyBG;
	Widget* DashBG;

	Widget* LightImage;
	Widget* HeavyImage;
	Widget* DashImage;

	Widget* LightCooldown;
	Widget* HeavyCooldown;
	Widget* DashCooldown;

};

