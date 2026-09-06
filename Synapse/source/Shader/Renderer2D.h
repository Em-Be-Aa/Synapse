#pragma once

#include "RenderComponent.h"
#include <glm/glm.hpp>
#include <vector>

class Shader;

class Renderer2D
{

public:

	static Renderer2D* GetRenderer()
	{
		static Renderer2D renderer;
		return &renderer;
	}

	void Init(const char* spriteVertexShaderPath, const char* spriteFragmentShaderPath);
	void Shutdown();
	void  BeginScene(const glm::mat4& worldView, const glm::mat4& worldProjection, const glm::mat4& screenView, const glm::mat4& screenProjection);
	void Submit(RenderComponent& rc);
	void Submit(unsigned int textureID, const glm::mat4& model, const glm::vec4& uvScaleOffset, const RenderSpace space);
	void DrawSubmissions(std::vector<Submission>& subs, unsigned int& currentTex);
	void EndScene();
	unsigned int GetDefaultTextureID() { return whiteTextureID; }

	// internal: immediate flush (simple, non-batched)
	void Flush();

private:

	Renderer2D() {};

	std::vector<Submission> worldSubmissions;
	std::vector<Submission> screenSubmissions;
	unsigned int quadVAO = 0, quadVBO = 0;
	Shader* spriteShader = nullptr;
	unsigned char whitePixel[4] = { 255, 255, 255, 255 };
	unsigned int whiteTextureID;

	glm::mat4 worldViewMatrix = glm::mat4(1.0f);
	glm::mat4 worldProjectionMatrix = glm::mat4(1.0f);
	glm::mat4 screenViewMatrix = glm::mat4(1.0f);
	glm::mat4 screenProjectionMatrix = glm::mat4(1.0f);
};

