#pragma once

#include "../Base/Widget.h"

class TextWidget;

class StatupCard : public Widget
{

public:

	StatupCard(CardInfo info);

	void Init() override;
	void Update(double dT) override;


private:

	CardInfo cardInfo;
	TextWidget* TitleText;
	TextWidget* DescText;

};

