#pragma once

#include <vector>
#include "../Shader/RenderComponent.h"


class RenderManager
{

private:

	RenderManager() {};


public:

	static RenderManager& GetRenderManager();
	std::vector<RenderComponent*> RenderComps;

};

// GetRenderManager is implemented in RenderManager.cpp

