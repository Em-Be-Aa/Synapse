#pragma once

#include "../Actor/Object.h"
#include <vector>

class TickManager
{

private:

	TickManager() {};

public:

	static TickManager* GetTickManager();
	void RegisterObject(Object* O);

	std::vector<Object*> RegisteredObjects;

};

