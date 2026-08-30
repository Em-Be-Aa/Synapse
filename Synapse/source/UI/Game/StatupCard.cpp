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
	SetSize({ 400.0f, 600.0f });
	SetOffset({ cardPosition, 0.0f });
	widgetSprite.Init("Assets/UI/Card_V2.png");
	SetZOrder(0);

	Font* fontA = Game::GetGame()->GetCurrentSession()->GetDefaultFont();
	Font* fontB = Game::GetGame()->GetCurrentSession()->GetSmallFont();


	// Wave Text
	TitleText = SpawnActor<TextWidget>(fontA, cardInfo.title);
	TitleText->SetColor({ 0.83f, 0.77f, 0.64f, 1.0f });
	TitleText->SetSize({ 30.0f, 30.0f });
	TitleText->SetOffset({ cardPosition, -50.0f });
	TitleText->SetAnchor(AnchorPoint::Center);
	TitleText->SetZOrder(1);

	DescText = SpawnActor<TextWidget>(fontB, cardInfo.description);
	DescText->SetColor({ 0.83f, 0.77f, 0.64f, 1.0f });
	DescText->SetSize({ 15.0f, 15.0f });
	DescText->SetOffset({ cardPosition, -130.0f });
	DescText->SetAnchor(AnchorPoint::Center);
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
