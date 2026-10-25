#pragma once

#include "AIState.h"
#include "StateMachine.h"

class ChaseState : public AIState
{

public:
	
	ChaseState(std::weak_ptr<StateMachine> stateM) : AIState(stateM) {};
	
	void Enter() override;
	void Update(double deltaTime) override;
	void Exit() override;
		 
};

