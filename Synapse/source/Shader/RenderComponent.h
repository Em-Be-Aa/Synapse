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

	
	RenderSpace space = RenderSpace::World;
	glm::mat4 model;
	glm::vec4 tint;
	int layer = 0;
	glm::vec4 uvScaleOffset;
	unsigned int textureID;
	bool textureXFlip = false;

	Object* GetOwner() const { return owner; }
	bool GetIsDisabled() const { return isDisabled; }
	void SetIsDisabled(bool disable) { isDisabled = disable; }

private:

	Object* owner;
	bool isDisabled = false;

};

