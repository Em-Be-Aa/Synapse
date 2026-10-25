#include "../../Actor/Actor.h"
#include "AIState.h"
#include "StateMachine.h"


AIState::AIState(std::weak_ptr<StateMachine> stateM)
{
	SM = stateM;
}

void AIState::Enter()
{

}

void AIState::Update(double deltaTime)
{

}

void AIState::Exit()
{

}
