#pragma once

#include "../Actor/Object.h"
#include "../Enums&Structs/GameTypes.h"
#include <glm/glm.hpp>
#include <memory>

class Object;

class RenderComponent : public Object
{

public:

	RenderComponent();
	~RenderComponent();

	void Init() override;
	void Update(double dT) override {};

	// non-copyable to avoid double registration
	RenderComponent(const RenderComponent&) = delete;
	RenderComponent& operator=(const RenderComponent&) = delete;

	QuadInfo defaultQuad;

	std::weak_ptr<Object> GetOwner() const { return owner; }
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

	void SetOwner(std::weak_ptr<Object> Owner)
	{
		owner = Owner;
	}

	std::vector<QuadInfo> Quads;


private:

	std::weak_ptr<Object> owner;
	bool isDisabled = false;


};

