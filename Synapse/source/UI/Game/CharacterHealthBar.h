#pragma once

#include "../Base/Widget.h"

class Character;

class CharacterHealthBar : public Widget
{

public:

	CharacterHealthBar(std::weak_ptr<Actor> Owner);

	void Init() override;

	void UpdateVigorBar(float Vigor, float MaxVigor);

};

