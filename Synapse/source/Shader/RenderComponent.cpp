#include "../Managers/RenderManager.h"
#include "RenderComponent.h"

RenderComponent::RenderComponent(Object* Owner) 
{
	RenderManager::GetRenderManager().RenderComps.push_back(this);
	defaultQuad.model = glm::mat4(1.0f);
	defaultQuad.tint = { 1.0f, 1.0f,1.0f ,1.0f };

	owner = Owner;
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
