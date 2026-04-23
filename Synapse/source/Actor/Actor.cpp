#include "Actor.h"
#include "ActorManager.h"
#include <iostream>

Actor::Actor()
{

	ActorManager* AM = ActorManager::GetActorManager();
	if (AM) 
	{
		AM->RegisterActor(this);
		std::cout << "Actor Registered!" << std::endl;
	}

	
}

void Actor::Init()
{
}

void Actor::Tick()
{
}
