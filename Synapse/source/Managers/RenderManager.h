#pragma once

#include "../Actor/Object.h"
#include "../Shader/RenderComponent.h"
#include <memory>
#include <vector>


class RenderManager
{

private:

	RenderManager() {};


public:

	static RenderManager& GetRenderManager();
	std::vector<std::weak_ptr<RenderComponent>> RenderComps;

	void DestoryPendingRenders()
	{
		std::erase_if(RenderComps, [](std::weak_ptr<RenderComponent> RC) 
			{ 
				if (RC.lock() && RC.lock()->GetOwner().lock())
				{
					return RC.lock()->GetOwner().lock()->isPendingDestroy;
				}
				else
				{
					return true;
				}
			});
	};

};

// GetRenderManager is implemented in RenderManager.cpp

