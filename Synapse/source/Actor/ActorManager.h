#pragma once
#include <vector>
#include "Actor.h"
class ActorManager
{

private:

	ActorManager() {};

public:

	static ActorManager* GetActorManager();
	void RegisterActor(Actor* Actor);

	std::vector<Actor*> RegisteredActors;

};

