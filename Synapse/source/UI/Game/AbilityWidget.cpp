#include "../../Characters/Player.h"
#include "../../Game/Game.h"
#include "../../Game/Session.h"
#include "../../Templates/Templates.h"
#include "../../Text/Font.h"
#include "../Base/TextWidget.h"
#include "../Base/Widget.h"
#include "AbilityWidget.h"
#include <format>
#include <iostream>

AbilityWidget::AbilityWidget(const char* ImagePath)
{
	imagePath = ImagePath;
}

AbilityWidget::AbilityWidget(const char* ImagePath, Widget* Parent)
{
	// This is not okay...i have to manually make constructor for each widget type to set parent...

	imagePath = ImagePath;
	parent = Parent;
}

void AbilityWidget::Init()
{
	Widget::Init();


	Font* fontA = Game::GetGame()->GetCurrentSession()->GetDefaultFont();

	SetImage("Assets/UI/StatBG.png");
	SetSize({ 100.0f, 100.0f });
	SetAnchor(AnchorPoint::BottomCenter);
	SetZOrder(0);


	Image = SpawnActor<Widget>(imagePath, this);
	Image->SetSize({ GetSize().x * 0.65, GetSize().y * 0.65 });
	Image->SetAnchor(AnchorPoint::Center);
	Image->SetZOrder(1);


	Cooldown = SpawnActor<Widget>(this);
	Cooldown->SetColor({ 0.11, 0.11, 0.11, 0.45f });
	Cooldown->SetSize({ GetSize().x * 0.7, GetSize().y * 0.7 });
	Cooldown->SetAnchor(AnchorPoint::Center);
	Cooldown->SetVisibility(false);
	Cooldown->SetZOrder(2);


	Text = SpawnActor<TextWidget>(fontA, "2", this);
	Text->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	Text->SetSize({ 30.0f, 30.0f });
	Text->SetAnchor(AnchorPoint::Center);
	Text->SetVisibility(false);
	Text->SetZOrder(3);

}

void AbilityWidget::Update(double dT)
{
	Widget::Update(dT);
}

void AbilityWidget::SetSize(glm::vec2 Size)
{
	Widget::SetSize(Size);

	if (Image && Cooldown)
	{
		Image->SetSize({ GetSize().x * 0.65, GetSize().y * 0.65 });
		Cooldown->SetSize({ GetSize().x * 0.7, GetSize().y * 0.7 });
	}

}
