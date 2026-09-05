#pragma once

#include "../../Actor/Object.h"
#include "../../Text/Font.h"
#include "TextWidget.h"

class HUD : public Object
{

public:

	HUD(Font* font) : defaultFont(font) {};
	void Update(double dT) override;
	void Init() override;

	void ShowCardsWidget(bool show);

private:

	Font* defaultFont;
};

