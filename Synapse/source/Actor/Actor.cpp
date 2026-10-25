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
	Object::Init();
	TickManager::GetTickManager()->RegisterObject(std::dynamic_pointer_cast<Actor>(shared_from_this()));
}

void Actor::Destroy()
{
	Object::Destroy();
}