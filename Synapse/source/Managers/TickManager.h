#pragma once

#include "../Actor/Actor.h"
#include <memory>
#include <vector>

class TickManager
{

private:

	TickManager() {};

public:

	static TickManager* GetTickManager();
	void RegisterObject(std::weak_ptr<Actor> O);

	void RemovePendingDestroyActors();

	std::vector<std::weak_ptr<Actor>> RegisteredActors;

};

