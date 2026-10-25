#pragma once

#include "../../Actor/Object.h"
#include "../../Shader/RenderComponent.h"
#include "../../Sprite/Sprite.h"
#include "../../Templates/Templates.h"
#include <vector>

class Actor;

class Widget : public Object
{

public:
	Widget() { widgetSprite = SpawnActor<Sprite>(); };
	Widget(const char* imagePath);

	Widget(std::weak_ptr<Widget> Parent) { parent = Parent; widgetSprite = SpawnActor<Sprite>();};
	Widget(const char* imagePath, std::weak_ptr<Widget> Parent);

	void Init() override;
	void Update(double dT) override;

	glm::vec3 CalculateWidgetPosition();
	glm::vec2 AnchorwithLocalOffset(AnchorPoint anchor, glm::vec2 offset);
	glm::vec2 GetRawAnchorPoint(AnchorPoint anchor, glm::vec2 offset);

protected:

	std::shared_ptr<RenderComponent> RenderComp;
	std::shared_ptr<Sprite> widgetSprite;
	glm::vec3 widgetPosition;
	glm::vec2 pixelSize = { 50.0f, 50.0f };
	glm::vec2 offset = { 0.00f, 0.0f };
	glm::vec4 widgetColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	int zOrder = 0;
	bool isVisible = true;

	std::weak_ptr<Actor> owner;
	std::weak_ptr<Widget> parent;

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

	virtual void SetSize(glm::vec2 Size)
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

	void SetOwner(std::weak_ptr<Actor> Owner)
	{
		owner = Owner;
	}

	void SetImage(const char* imagePath)
	{
		widgetSprite->Init(imagePath);
	}

	void SetVisibility(bool value)
	{
		isVisible = value;
	}

	bool GetVisibility()
	{
		return isVisible;
	}

	glm::vec3 GetPosition()
	{
		return widgetPosition;
	}

};

