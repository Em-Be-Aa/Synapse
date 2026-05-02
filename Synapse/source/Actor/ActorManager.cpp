#include "ActorManager.h"

ActorManager* ActorManager::GetActorManager()
{
	static ActorManager DefaultActorManager;

	return &DefaultActorManager;
}

void ActorManager::RegisterActor(Actor* Actor)
{
	RegisteredActors.push_back(Actor);
}
