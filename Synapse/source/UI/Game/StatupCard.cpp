#include "../../Game/Game.h"
#include "../../Game/Session.h"
#include "../../Templates/Templates.h"
#include "../../Text/Font.h"
#include "../Base/TextWidget.h"
#include "StatupCard.h"
#include <iostream>


StatupCard::StatupCard(CardInfo info, float position)
{
	cardInfo = info;
	cardPosition = position;
}

void StatupCard::Init()
{
	Button::Init();

	SetAnchor(AnchorPoint::Center);
	SetSize({ 900.0f, 200.0f });
	SetOffset({ 0.0f, cardPosition });
	widgetSprite.Init("Assets/UI/Card.png");
	SetZOrder(0);

	Font* fontA = Game::GetGame()->GetCurrentSession()->GetLargeFont();
	Font* fontB = Game::GetGame()->GetCurrentSession()->GetSmallFont();


	StatIcon = SpawnActor<AbilityWidget>(cardInfo.icon.c_str(), this);
	StatIcon->SetSize({ 75.0f, 75.0f });
	StatIcon->SetOffset({ 25.0f, 25.0f });
	StatIcon->SetAnchor(AnchorPoint::TopLeft);
	StatIcon->SetZOrder(1);

	TitleText = SpawnActor<TextWidget>(fontA, cardInfo.title, this);
	TitleText->SetColor({ 1, 1, 1, 1.0f });
	TitleText->SetOffset({ 120.0f, 30.0f });
	TitleText->SetAnchor(AnchorPoint::TopLeft);
	TitleText->SetZOrder(1);

	DescText = SpawnActor<TextWidget>(fontB, cardInfo.description, this);
	DescText->SetColor({ 1, 1, 1, 1.0f });
	DescText->SetOffset({ 120.0f, 110.0f });
	DescText->SetAnchor(AnchorPoint::TopLeft);
	DescText->SetZOrder(1);

}

void StatupCard::Update(double dT)
{
	Button::Update(dT);
}

void StatupCard::Destroy()
{
	TitleText->Destroy();
	DescText->Destroy();

	Object::Destroy();
}
