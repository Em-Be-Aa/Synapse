#pragma once

#include "../Base/Widget.h"

class HealthWidget : public Widget
{

public:

	HealthWidget() {};

	void Init() override;

	void UpdateVigorBar(float Vigor, float MaxVigor);
	void UpdatePlatingBar(float Plating, float MaxPlating);


private:

	Widget* VigorBar;
	Widget* PlatingBar;

	TextWidget* VigorText;
	TextWidget* PlatingText;
};

