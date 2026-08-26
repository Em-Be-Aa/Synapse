#include "../../Characters/Character.h"
#include "../../Characters/Player.h"
#include "../../Game/Game.h"
#include "../../Game/Session.h"
#include "../../Shader/Renderer2D.h"
#include "CharacterHealthBar.h"
#include <iostream>

CharacterHealthBar::CharacterHealthBar(Actor* Owner)
{
	owner = Owner;
}

void CharacterHealthBar::Init()
{
	SetAnchor(AnchorPoint::None);
	SetSize({ 0.3f, 0.025f });
	SetOffset({0.0f, 0.1f + 0.0f });
	SetColor({ 0.49f, 0.255f, 0.251f, 1.0f });
	SetRenderSpace(RenderSpace::World);
	SetZOrder(0);

	auto ownerCharacter = dynamic_cast<Character*>(owner);
	ownerCharacter->GetVitalsComponent().onVigorChanged.Subscribe
	(
		[this](float VigorPer) { this->UpdateVigorBar(VigorPer); }
	);
}

void CharacterHealthBar::UpdateVigorBar(float VigorPer)
{
	// remove the hardcoded x value...save the initial and use that...
	SetSize({ 0.3f * VigorPer, GetSize().y });
}
