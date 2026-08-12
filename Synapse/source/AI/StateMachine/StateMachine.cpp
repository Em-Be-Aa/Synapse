#include "AttackState.h"
#include "ChaseState.h"
#include "StateMachine.h"
#include <iostream>

StateMachine::StateMachine(Enemy* Owner, Player* Player)
{
	owner = Owner;
	player = Player;

	SetState<ChaseState>(this);
}

void StateMachine::Update(double dt)
{
	bool isOverlapping = owner->GetCollisionComponent().IsCurrentCollidor(&player->GetCollisionComponent());

	if(isOverlapping)
	{
		SetState<AttackState>(this);
	}
	
}

