#pragma once

#include "../Base/Widget.h"

class TextWidget;

class AbilityWidget : public Widget
{

public:

	AbilityWidget(const char* ImagePath);
	AbilityWidget(const char* ImagePath, std::weak_ptr<Widget> Parent);
	void Init() override;
	void Update(double dT) override;
	void SetSize(glm::vec2 Size) override;


private:

	std::shared_ptr<Widget> Cooldown;
	std::shared_ptr<TextWidget> Text;
	std::shared_ptr<Widget> Image;

	const char* imagePath;


public:

	std::weak_ptr<Widget> GetCooldown()
	{
		return Cooldown;
	}

	std::weak_ptr<TextWidget> GetText()
	{
		return Text;
	}

	std::weak_ptr<Widget> GetImage()
	{
		return Image;
	}
};

