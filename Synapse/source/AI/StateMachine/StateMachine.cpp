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
	bool isOverlapping = owner->GetCollisionComponent().IsCurrentCollidor(&player->GetCollisionComponent());

	if(isOverlapping)
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

