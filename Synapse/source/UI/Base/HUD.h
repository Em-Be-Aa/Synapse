#pragma once

#include "../../Actor/Object.h"
#include "../../Text/Font.h"
#include "TextWidget.h"

class HUD : public Object
{

public:

	HUD(std::weak_ptr<Font> font) : defaultFont(font) {};
	void Update(double dT) override;
	void Init() override;

	void ShowCardsWidget(bool show);

private:

	std::weak_ptr<Font> defaultFont;
};

