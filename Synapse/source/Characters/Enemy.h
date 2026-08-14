#pragma once
#include "Character.h"

class StateMachine;

class Enemy: public Character 
{

public:

	Enemy();

	void Tick(double deltaTime) override;

	void Destroy() override;

	StateMachine* AIStateMachine;
};

