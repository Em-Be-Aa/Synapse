#include "ActorManager.h"

ActorManager* ActorManager::GetActorManager()
{

	static ActorManager* DefaultActorManager = new ActorManager();

	return DefaultActorManager;

}

void ActorManager::RegisterActor(Actor* Actor)
{
	RegisteredActors.push_back(Actor);
}
