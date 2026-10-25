#pragma once

#include "../Base/Widget.h"
#include "AbilityWidget.h"

class TextWidget;

class VitalsWidget : public Widget
{

public:

	void Init() override;
	void Update(double dT) override;


private:

	std::shared_ptr<AbilityWidget> Momentum;
	std::shared_ptr<AbilityWidget> Focus;
	std::shared_ptr<AbilityWidget> Recovery;
	std::shared_ptr<AbilityWidget> Insight;

};

