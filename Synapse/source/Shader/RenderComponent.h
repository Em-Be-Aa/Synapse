#pragma once

#include <glm/glm.hpp>

class RenderComponent
{

public:

	RenderComponent();
	~RenderComponent();

	// non-copyable to avoid double registration
	RenderComponent(const RenderComponent&) = delete;
	RenderComponent& operator=(const RenderComponent&) = delete;

	glm::mat4 model;
	int layer = 0;
	glm::vec4 uvScaleOffset;
	unsigned int textureID;
	bool textureXFlip = false;


};

