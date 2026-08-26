#pragma once

#include "../Base/Widget.h"

class Character;

class CharacterHealthBar : public Widget
{

public:

	CharacterHealthBar(Actor* Owner);

	void Init() override;

	void UpdateVigorBar(float VigorPer);

};

