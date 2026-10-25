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

	std::shared_ptr<Widget> VigorBar;
	std::shared_ptr<Widget> PlatingBar;

	std::shared_ptr<TextWidget> VigorText;
	std::shared_ptr<TextWidget> PlatingText;
};

