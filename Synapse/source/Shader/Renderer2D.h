
#pragma once

#include <glm/glm.hpp>
#include "RenderComponent.h"

namespace Renderer2D
{
	void Init(const char* spriteVertexShaderPath, const char* spriteFragmentShaderPath);
	void Shutdown();

	void BeginScene(const glm::mat4& view, const glm::mat4& projection);
	void Submit(const RenderComponent& rc);
	void Submit(unsigned int textureID, const glm::mat4& model, const glm::vec4& uvScaleOffset);
	void EndScene();

	// internal: immediate flush (simple, non-batched)
	void Flush();
}

