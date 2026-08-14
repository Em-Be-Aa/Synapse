#pragma once

#include "../../Actor/Object.h"
#include "../../Characters/Character.h"
#include "../../Characters/Enemy.h"
#include "../../Characters/Player.h"
#include "AIState.h"


class StateMachine : public Object
{

public:

	StateMachine(Enemy* Owner, Player* Player);

	void Update(double dt) override;

	template<typename T>
	void SetState(StateMachine* SM)
	{
		if (dynamic_cast<T*>(currentState) != nullptr)
		{
			return;
		}

		if (currentState)
		{
			currentState->Exit();
			currentState->Destroy();
		}

		auto CS = SpawnActor<T>(SM);
		currentState = CS;
		currentState->Enter();
	
	}

	AIState* GetCurrentState()
	{
		return currentState;
	}

	void Destroy() override;


	Player* GetPlayer() { return player; }
	Enemy* GetOwner() { return owner; }

private:

	Enemy* owner;
	Player* player;

	AIState* currentState;
};

