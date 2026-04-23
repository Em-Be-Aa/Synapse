#pragma once
#include <vector>
#include "Actor.h"
class ActorManager
{


private:

	ActorManager() {};

public:

	static ActorManager* GetActorManager();

	std::vector<Actor*> RegisteredActors;

	void RegisterActor(Actor* Actor);

};

