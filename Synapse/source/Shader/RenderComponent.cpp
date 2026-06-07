#include "RenderComponent.h"
#include "../Managers/RenderManager.h"

RenderComponent::RenderComponent() 
{
	RenderManager::GetRenderManager().RenderComps.push_back(this);
	model = glm::mat4(1.0f);

}

RenderComponent::~RenderComponent()
{
	auto &list = RenderManager::GetRenderManager().RenderComps;
	for (auto it = list.begin(); it != list.end(); ++it)
	{
		if (*it == this)
		{
			list.erase(it);
			break;
		}
	}
}
