#pragma once

#include "../Base/Widget.h"
#include "AbilityWidget.h"

class TextWidget;

class AbilitiesWidget : public Widget
{

public:

	void Init() override;
	void Update(double dT) override;


private:

	AbilityWidget* Light;
	AbilityWidget* Heavy;
	AbilityWidget* Dash;


};

