#pragma once

#include "../../Actor/Object.h"
#include "../../Shader/RenderComponent.h"
#include "../../Sprite/Sprite.h"
#include <vector>

class Actor;

class Widget : public Object
{

public:
	Widget() : RenderComp(this) {};
	Widget(const char* imagePath);

	void Update(double dT) override;

	glm::vec3 CalculateWidgetPosition();
	glm::vec2 AnchorwithLocalOffset(AnchorPoint anchor, glm::vec2 offset);
	glm::vec2 GetRawAnchorPoint(AnchorPoint anchor, glm::vec2 offset);

protected:

	RenderComponent RenderComp;
	Sprite widgetSprite;
	glm::vec3 widgetPosition;
	glm::vec2 pixelSize = { 50.0f, 50.0f };
	glm::vec2 offset = { 0.00f, 0.0f };
	glm::vec4 widgetColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	int zOrder = 0;

	Actor* owner = nullptr;

	AnchorPoint widgetAnchor = AnchorPoint::TopRight;
	RenderSpace widgetRenderSpace = RenderSpace::Screen;


public:


	void SetAnchor(AnchorPoint anchor)
	{
		widgetAnchor = anchor;
	}

	void SetOffset(glm::vec2 Offset)
	{
		offset = Offset;
	}

	void SetSize(glm::vec2 Size)
	{
		pixelSize = Size;
	}

	void SetZOrder(int Z)
	{
		zOrder = Z;
	}

	void SetColor(glm::vec4 Color)
	{
		widgetColor = Color;
	}

	void SetRenderSpace(RenderSpace RS)
	{
		widgetRenderSpace = RS;
	}

	glm::vec2 GetSize()
	{
		return pixelSize;
	}

	void SetOwner(Actor* Owner)
	{
		owner = Owner;
	}


};

