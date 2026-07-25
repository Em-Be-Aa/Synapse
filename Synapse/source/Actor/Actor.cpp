#include "../Managers/TickManager.h"
#include "Actor.h"


Actor::Actor()
{
}

Actor::~Actor()
{
}

void Actor::Init()
{
	TickManager::GetTickManager()->RegisterObject(this);
}

void Actor::Destroy()
{

}

