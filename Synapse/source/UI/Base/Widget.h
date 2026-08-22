#pragma once

#include "../../Actor/Object.h"
#include "../../Shader/RenderComponent.h"
#include "../../Sprite/Sprite.h"
#include <vector>

class Widget : public Object
{

public:
	Widget() : RenderComp(this) {};
	Widget(glm::vec2 widgetSize, glm::vec2 offset);
	Widget(const char* imagePath, glm::vec2 widgetSize, glm::vec2 offset);

	glm::vec2 AnchorwithLocalOffset(AnchorPoint anchor, glm::vec2 offset);
	glm::vec2 GetRawAnchorPoint(AnchorPoint anchor, glm::vec2 offset);

	void Update(double dT) override;

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

protected:

	RenderComponent RenderComp;
	Sprite widgetSprite;
	glm::vec2 pixelSize = { 50.0f, 50.0f };
	glm::vec2 offset = { 0.00f, 0.0f };
	glm::vec4 widgetColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	AnchorPoint widgetAnchor = AnchorPoint::TopRight;
	int zOrder = 0;

};

