#pragma once

#include "../Base/Widget.h"

class TextWidget;

class VitalsWidget : public Widget
{

public:

	void Init() override;
	void Update(double dT) override;


private:

	Widget* VigorBG;
	Widget* PlatingBG;
	Widget* MomentumBG;
	Widget* FocusBG;
	Widget* RecoveryBG;
	Widget* InsightBG;

	TextWidget* VigorText;
	TextWidget* PlatingText;
	TextWidget* MomentumText;
	TextWidget* FocusText;
	TextWidget* RecoveryText;
	TextWidget* InsightText;

};

