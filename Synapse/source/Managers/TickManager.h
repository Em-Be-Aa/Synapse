#pragma once

#include "../Actor/Actor.h"
#include <vector>

class TickManager
{

private:

	TickManager() {};

public:

	static TickManager* GetTickManager();
	void RegisterObject(Actor* O);

	void RemovePendingDestroyActors();

	std::vector<Actor*> RegisteredActors;

};

