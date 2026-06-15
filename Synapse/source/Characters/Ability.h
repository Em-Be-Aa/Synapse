#pragma once
#include "../Sprite/Animator.h"
#include <string>


class Ability
{

public:

	Ability(std::string abilTag, Animator* animator);

	void Activate();

	unsigned ID = 0;

	std::string tag = "";

	Animator* targetAnimator;


private:

	float cooldowm = 3.0f;


};

