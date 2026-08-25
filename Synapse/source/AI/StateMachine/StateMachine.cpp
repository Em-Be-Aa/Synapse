#include "AttackState.h"
#include "ChaseState.h"
#include "StateMachine.h"
#include <iostream>

StateMachine::StateMachine(Enemy* Owner, Player* Player)
{
	owner = Owner;
	player = Player;
}

void StateMachine::Update(double dt)
{
	// Add functions to check edge distances not centers
	glm::vec3 difference = player->Position - owner->Position;
	float distance = glm::length(difference);

	// For now dead players when animation is running for death have chase mode on...in the future add a default mode
	if(distance < 0.25 && owner->GetAliveStatus())
	{
		SetState<AttackState>(this);
	}
	else
	{
		SetState<ChaseState>(this);
	}
	
}

void StateMachine::Destroy()
{
	Object::Destroy();

	GetCurrentState()->Destroy();
}

