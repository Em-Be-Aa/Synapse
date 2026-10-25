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

	std::shared_ptr<AbilityWidget> Light;
	std::shared_ptr<AbilityWidget> Heavy;
	std::shared_ptr<AbilityWidget> Dash;


};

