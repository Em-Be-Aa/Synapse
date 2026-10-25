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

	std::shared_ptr<TextWidget> WaveText;
	std::shared_ptr<TextWidget> WaveInfoText;

};

