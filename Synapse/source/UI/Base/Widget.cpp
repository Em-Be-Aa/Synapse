#include "../../Game/Game.h"
#include "../../Shader/Renderer2D.h"
#include "../../Window/Window.h"
#include "Widget.h"
#include <glm/ext/matrix_transform.hpp>

Widget::Widget() : RenderComp(this)
{

}

Widget::Widget(glm::vec2 widgetSize, glm::vec2 Position) : RenderComp(this), normalizedPos(Position)
{

}


Widget::Widget(const char* imagePath, glm::vec2 widgetSize, glm::vec2 Position) : RenderComp(this), widgetSprite(imagePath), normalizedPos(Position)
{
    pixelSize = widgetSize;
}

void Widget::Update(double dT)
{
    //float windowWidth = Game::GetGame().GetGameWindow()->GetWindowWidth();
    //float windowHeight = Game::GetGame().GetGameWindow()->GetWindowHeight();

    float windowWidth = 800;
    float windowHeight = 600;

    float pixelX = normalizedPos.x * windowWidth;
    float pixelY = normalizedPos.y * windowHeight;
    glm::vec2 centerPixel = { pixelX + pixelSize.x * 0.5f, pixelY + pixelSize.y * 0.5f };
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(centerPixel, 0.0f));
    model = glm::scale(model, glm::vec3(pixelSize, 1.0f));
    glm::vec4 uv = glm::vec4(1.0f, 1.0f, 0.0f, 0.0f);

    RenderComp.uvScaleOffset = uv;
    RenderComp.space = RenderSpace::Screen;
    RenderComp.model = model;
    RenderComp.tint = widgetColor;

    if (widgetSprite.DefaultImage)
    {
        RenderComp.textureID = widgetSprite.DefaultImage->ID;
    }

    Renderer2D::GetRenderer()->Submit(RenderComp);
}
