#pragma once

#include "../Actor/Object.h"
#include "../Shader/RenderComponent.h"
#include <vector>


class RenderManager
{

private:

	RenderManager() {};


public:

	static RenderManager& GetRenderManager();
	std::vector<RenderComponent*> RenderComps;

	void DestoryPendingRenders()
	{
		std::erase_if(RenderComps, [](const RenderComponent* RC) { return RC->GetOwner()->isPendingDestroy; });
	};

};

// GetRenderManager is implemented in RenderManager.cpp

