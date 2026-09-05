#pragma once

#include "../Base/Widget.h"

class TextWidget;

class AbilityWidget : public Widget
{

public:

	AbilityWidget(const char* ImagePath);
	AbilityWidget(const char* ImagePath, Widget* Parent);
	void Init() override;
	void Update(double dT) override;
	void SetSize(glm::vec2 Size) override;

private:

	Widget* Image;
	Widget* Cooldown;
	TextWidget* Text;

	const char* imagePath;


public:

	Widget* GetCooldown()
	{
		return Cooldown;
	}

	TextWidget* GetText()
	{
		return Text;
	}
};

