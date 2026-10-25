#pragma once

#include "../Base/Button.h"
#include "AbilityWidget.h"

class TextWidget;

class StatupCard : public Button
{

public:

	StatupCard(CardInfo info, float position);

	void Init() override;
	void Update(double dT) override;

	void Destroy() override;

	CardInfo GetCardInfo()
	{
		return cardInfo;
	};

private:

	CardInfo cardInfo;
	float cardPosition;

	std::shared_ptr<AbilityWidget> StatIcon;
	std::shared_ptr<TextWidget> TitleText;
	std::shared_ptr<TextWidget> DescText;

};

