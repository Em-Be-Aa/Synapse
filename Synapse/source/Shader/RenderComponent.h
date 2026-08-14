#pragma once

#include "../Actor/Object.h"
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

	glm::mat4 model;
	int layer = 0;
	glm::vec4 uvScaleOffset;
	unsigned int textureID;
	bool textureXFlip = false;

	Object* GetOwner() const { return owner; }

private:

	Object* owner;


};

