#include "AttackState.h"
#include "ChaseState.h"
#include "StateMachine.h"
#include <iostream>

StateMachine::StateMachine(std::weak_ptr<Enemy> Owner, std::weak_ptr<Player> Player)
{
	owner = Owner;
	player = Player;
}

void StateMachine::Update(double dt)
{
	// Add functions to check edge distances not centers
	auto Player = player.lock();
	auto Owner = owner.lock();

	if (!Player || !Owner)
	{
		return;
	}

	glm::vec3 difference = Player->GetPosition() - Owner->GetPosition();
	float distance = glm::length(difference);

	// For now dead players when animation is running for death have chase mode on...in the future add a default mode
	if(distance < 0.25 && Owner->GetAliveStatus())
	{
		SetState<AttackState>(std::dynamic_pointer_cast<StateMachine>(shared_from_this()));
	}
	else
	{
		SetState<ChaseState>(std::dynamic_pointer_cast<StateMachine>(shared_from_this()));
	}
	
}

void StateMachine::Destroy()
{
	Object::Destroy();

	GetCurrentState().lock()->Destroy();
}

