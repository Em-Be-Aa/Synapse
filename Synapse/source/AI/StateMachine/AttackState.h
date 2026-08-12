#pragma once

#include "AIState.h"
#include "StateMachine.h"

class AttackState : public AIState
{

public:

	AttackState(StateMachine* stateM) : AIState(stateM) {};

	void Enter() override;
	void Update(double deltaTime) override;
	void Exit() override;

};

