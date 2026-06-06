#include "Object.h"
#include "../Managers/TickManager.h"

Object::Object()
{
	TickManager::GetTickManager()->RegisterObject(this);
}
