#pragma once

#include "../../Actor/Object.h"

class StateMachine;

class AIState : public Object
{

public:

	AIState(StateMachine* stateM);
	
	virtual void Enter();
	void Update(double deltaTime) override;
	virtual void Exit();


	StateMachine* SM;
};

