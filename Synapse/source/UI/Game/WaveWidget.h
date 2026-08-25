#pragma once

#include "../Base/Widget.h"

class TextWidget;

class WaveWidget : public Widget
{

public:

	WaveWidget() {};

	void Init() override;
	void Update(double dT) override;


private:

	TextWidget* WaveText;
	TextWidget* WaveInfoText;

};

