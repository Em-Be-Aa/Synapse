#pragma once

#include "../../Actor/Object.h"
#include "../../Characters/Enemy.h"
#include "../../Characters/Player.h"
#include "../../Templates/Templates.h"
#include "AIState.h"


class StateMachine : public Object
{

public:

	StateMachine(std::weak_ptr<Enemy> Owner, std::weak_ptr<Player> Player);

	void Update(double dt) override;

	template<typename T>
	void SetState(std::weak_ptr<StateMachine> SM)
	{
		if (std::dynamic_pointer_cast<std::shared_ptr<T>>(currentState) != nullptr)
		{
			return;
		}

		if (currentState)
		{
			currentState->Exit();
			currentState->Destroy();
		}

		currentState = SpawnActor<T>(SM);
		currentState->Enter();
	
	}

	void Destroy() override;

	std::weak_ptr<AIState> GetCurrentState() { return currentState; }
	std::weak_ptr<Player> GetPlayer() { return player; }
	std::weak_ptr<Enemy> GetOwner() { return owner; }

private:

	std::weak_ptr< Enemy> owner;
	std::weak_ptr<Player> player;
	std::shared_ptr<AIState> currentState;
};

