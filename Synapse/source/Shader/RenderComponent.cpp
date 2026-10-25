#include "../Managers/RenderManager.h"
#include "RenderComponent.h"

RenderComponent::RenderComponent()
{
	defaultQuad.model = glm::mat4(1.0f);
	defaultQuad.tint = { 1.0f, 1.0f,1.0f ,1.0f };
}

RenderComponent::~RenderComponent()
{
//	auto& list = RenderManager::GetRenderManager().RenderComps;
//	for (auto it = list.begin(); it != list.end(); ++it)
//	{
//		if (*it.lock() == std::dynamic_pointer_cast<RenderComponent>(shared_from_this()))
//		{
//			list.erase(it);
//			break;
//		}
//	}
}

void RenderComponent::Init()
{
	RenderManager::GetRenderManager().RenderComps.push_back(std::dynamic_pointer_cast<RenderComponent>(shared_from_this()));
}
