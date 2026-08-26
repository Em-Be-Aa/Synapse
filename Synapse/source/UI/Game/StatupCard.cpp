#include "../../Game/Game.h"
#include "../../Game/Session.h"
#include "../../Text/Font.h"
#include "../Base/TextWidget.h"
#include "StatupCard.h"


StatupCard::StatupCard(CardInfo info)
{
	cardInfo = info;
}

void StatupCard::Init()
{
	SetAnchor(AnchorPoint::Center);
	SetSize({ 400.0f, 600.0f });
	SetOffset({ 20.0f, 20.0f });
	widgetSprite.Init("Assets/UI/Card.png");
	SetZOrder(0);

	Font* font = Game::GetGame()->GetCurrentSession()->GetDefaultFont();

	// Wave Text
	TitleText = SpawnActor<TextWidget>(font, cardInfo.title);
	TitleText->SetColor({ 0.83f, 0.77f, 0.64f, 1.0f });
	TitleText->SetSize({ 30.0f, 30.0f });
	TitleText->SetOffset({ 160.0f, 44.0f });
	TitleText->SetAnchor(AnchorPoint::Center);
	TitleText->SetZOrder(1);

	DescText = SpawnActor<TextWidget>(font, cardInfo.description);
	DescText->SetColor({ 0.83f, 0.77f, 0.64f, 1.0f });
	DescText->SetSize({ 15.0f, 15.0f });
	DescText->SetOffset({ 183.0f, 95.0f });
	DescText->SetAnchor(AnchorPoint::Center);
	DescText->SetZOrder(1);



}

void StatupCard::Update(double dT)
{
	Widget::Update(dT);
}
