#pragma once

#include "../../Actor/Object.h"
#include "../../Shader/RenderComponent.h"
#include "../../Sprite/Sprite.h"
#include <vector>

class Widget : public Object
{

public:

	Widget();
	Widget(glm::vec2 widgetSize, glm::vec2 Position);
	Widget(const char* imagePath, glm::vec2 widgetSize, glm::vec2 Position);

	void Update(double dT) override;


protected:

	RenderComponent RenderComp;
	Sprite widgetSprite;
	glm::vec2 pixelSize = { 50.0f, 50.0f };
	glm::vec2 normalizedPos = { 0.04f, 0.9f };
	glm::vec4 widgetColor = { 1.0f, 1.0f, 1.0f, 1.0f };

	std::vector<Widget> childWidgets;
};

