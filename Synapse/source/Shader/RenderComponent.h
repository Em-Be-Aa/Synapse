#pragma once

#include "../Actor/Object.h"
#include "../Enums&Structs/GameTypes.h"
#include <glm/glm.hpp>

class Object;

class RenderComponent
{

public:

	RenderComponent(Object* Owner);
	~RenderComponent();

	// non-copyable to avoid double registration
	RenderComponent(const RenderComponent&) = delete;
	RenderComponent& operator=(const RenderComponent&) = delete;

	QuadInfo defaultQuad;

	Object* GetOwner() const { return owner; }
	bool GetIsDisabled() const { return isDisabled; }
	void SetIsDisabled(bool disable) { isDisabled = disable; }
	std::vector<QuadInfo> GetQuads()
	{
		if (Quads.empty())
		{
			Quads.push_back(defaultQuad);
		}

		return Quads;
	}

	void ClearQuads()
	{
		Quads.clear();
	}

	std::vector<QuadInfo> Quads;


private:

	Object* owner;
	bool isDisabled = false;


};

