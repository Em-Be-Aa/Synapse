#pragma once

#include "../Base/Widget.h"

class HealthWidget : public Widget
{

public:

	HealthWidget() {};

	void Init() override;

	void UpdateHealthBar(float BaseHealthPer, float ArmorHealthPer);


private:

	Widget* HealthBar;
	Widget* ArmorBar;
};

