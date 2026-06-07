#include "RenderManager.h"

RenderManager& RenderManager::GetRenderManager()
{
	static RenderManager Manager;
	
	return Manager;
}
