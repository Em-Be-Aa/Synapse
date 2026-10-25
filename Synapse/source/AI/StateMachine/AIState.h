#pragma once

#include "../../Actor/Object.h"
#include <memory>

class StateMachine;

class AIState : public Object
{

public:

	AIState(std::weak_ptr<StateMachine> stateM);
	
	virtual void Enter();
	void Update(double deltaTime) override;
	virtual void Exit();


	std::weak_ptr<StateMachine> SM;
};

