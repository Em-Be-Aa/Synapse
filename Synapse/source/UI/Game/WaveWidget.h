#pragma once

#include "../Base/Widget.h"

class TextWidget;

class WaveWidget : public Widget
{

public:

	WaveWidget() {};

	void Init() override;


private:

	TextWidget* WaveText;

};

