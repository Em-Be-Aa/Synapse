#include "../../Game/Game.h"
#include "../../Shader/Renderer2D.h"
#include "../../Window/Window.h"
#include "Widget.h"
#include <glm/ext/matrix_transform.hpp>


Widget::Widget(const char* imagePath) : RenderComp(this), widgetSprite(imagePath)
{

}

void Widget::Update(double dT)
{
    widgetPosition = CalculateWidgetPosition();

    glm::mat4 model = glm::translate(glm::mat4(1.0f), widgetPosition);
    model = glm::scale(model, glm::vec3(GetSize(), 1.0f));
    glm::vec4 uv = glm::vec4(1.0f, 1.0f, 0.0f, 0.0f);

    RenderComp.uvScaleOffset = uv;
    RenderComp.space = widgetRenderSpace;
    RenderComp.model = model;
    RenderComp.tint = widgetColor;
    RenderComp.layer = zOrder;

    if (widgetSprite.DefaultImage)
    {
        RenderComp.textureID = widgetSprite.DefaultImage->ID;
    }

    Renderer2D::GetRenderer()->Submit(RenderComp);

}

glm::vec3 Widget::CalculateWidgetPosition()
{
    if (widgetRenderSpace == RenderSpace::Screen)
    {
        return glm::vec3(AnchorwithLocalOffset(widgetAnchor, offset), 0.0f);
    }
    else if (widgetRenderSpace == RenderSpace::World)
    {
        return  owner->Position + glm::vec3(offset, 0.0f);
    }
}



glm::vec2 Widget::AnchorwithLocalOffset(AnchorPoint anchor, glm::vec2 Offset)
{
    float windowWidth = Game::GetGame()->GetGameWindow()->GetWindowWidth();
    float windowHeight = Game::GetGame()->GetGameWindow()->GetWindowHeight();

    glm::vec2 centerPixel;

    switch (anchor)
    {
    case AnchorPoint::TopLeft: { return { pixelSize.x * 0.5f + Offset.x, windowHeight - pixelSize.y * 0.5f - Offset.y }; }
                             break;
    case AnchorPoint::BottomLeft: { return  { pixelSize.x * 0.5f + Offset.x, pixelSize.y * 0.5f + Offset.y }; }
                                break;
    case AnchorPoint::TopRight: { return  { windowWidth - pixelSize.x * 0.5f - Offset.x, windowHeight - pixelSize.y * 0.5f - Offset.y }; }
                              break;
    case AnchorPoint::BottomRight: { return  { windowWidth - pixelSize.x * 0.5f - Offset.x, pixelSize.y * 0.5f + Offset.y }; }
                                 break;
    case AnchorPoint::Center: { return  { windowWidth/2 + Offset.y, windowHeight/2 + Offset.y }; }
                            break;
    case AnchorPoint::None: { return  {  pixelSize.x * 0.5f + Offset.y, pixelSize.y * 0.5f + Offset.y }; }
                          break;
    default: { return  { windowWidth + pixelSize.x * 0.5f + Offset.y, windowHeight + pixelSize.y * 0.5f + Offset.y }; }
           break;
    }
}

glm::vec2 Widget::GetRawAnchorPoint(AnchorPoint anchor, glm::vec2 offset)
{
    float w = Game::GetGame()->GetGameWindow()->GetWindowWidth();
    float h = Game::GetGame()->GetGameWindow()->GetWindowHeight();

    switch (anchor)
    {
    case AnchorPoint::TopLeft:     return { offset.x, h - offset.y };
    case AnchorPoint::BottomLeft:  return { offset.x, offset.y };
    case AnchorPoint::TopRight:    return { w - offset.x, h - offset.y };
    case AnchorPoint::BottomRight: return { w - offset.x, offset.y };
    case AnchorPoint::Center:      return { w * 0.5f + offset.x, h * 0.5f + offset.y };
    default: return { offset.x, offset.y };
    }
}
