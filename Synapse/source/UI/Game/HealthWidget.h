#pragma once

#include "../Base/Widget.h"

class HealthWidget : public Widget
{

public:

	HealthWidget() {};

	void Init() override;

	void UpdateVigorBar(float VigorPer);
	void UpdatePlatingBar(float PlatingPer);


private:

	Widget* VigorBar;
	Widget* PlatingBar;
};

