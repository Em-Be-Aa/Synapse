#include "TickManager.h"

// This should be Tick Manager...every spawnable thing and managers should implement ITicker and by of some object class which will have tick bool and if tick for that object will run for the game.
TickManager* TickManager::GetTickManager()
{
	static TickManager DefaultTickManager;

	return &DefaultTickManager;
}

void TickManager::RegisterObject(Object* O)
{
	RegisteredObjects.push_back(O);
}


