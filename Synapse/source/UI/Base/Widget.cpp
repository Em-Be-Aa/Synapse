#include "../../Game/Game.h"
#include "../../Shader/Renderer2D.h"
#include "../../Window/Window.h"
#include "Widget.h"
#include <glm/ext/matrix_transform.hpp>


Widget::Widget(const char* imagePath) : RenderComp(this), widgetSprite(imagePath)
{

}

Widget::Widget(const char* imagePath, Widget* Parent) : RenderComp(this), widgetSprite(imagePath), parent(Parent)
{

}

void Widget::Update(double dT)
{
    widgetPosition = CalculateWidgetPosition();

    glm::mat4 model = glm::translate(glm::mat4(1.0f), widgetPosition);
    model = glm::scale(model, glm::vec3(GetSize(), 1.0f));
    glm::vec4 uv = glm::vec4(1.0f, 1.0f, 0.0f, 0.0f);

    RenderComp.defaultQuad.uvScaleOffset = uv;
    RenderComp.defaultQuad.space = widgetRenderSpace;
    RenderComp.defaultQuad.model = model;
    RenderComp.defaultQuad.tint = widgetColor;
    RenderComp.defaultQuad.layer = zOrder;

    if (widgetSprite.DefaultImage)
    {
        RenderComp.defaultQuad.textureID = widgetSprite.DefaultImage->ID;
    }

    RenderComp.SetIsDisabled(!isVisible);
 
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
    float parentPositionX = 0.0f;
    float parentPositionY = 0.0f;
    float CenterAdjustX = pixelSize.x * 0.5f;
    float CenterAdjustY = pixelSize.y * 0.5f;

    if (parent)
    {
        windowWidth = parent->GetSize().x;
        windowHeight = parent->GetSize().y;
        parentPositionX = parent->GetPosition().x - parent->GetSize().x/2;
        parentPositionY = parent->GetPosition().y - parent->GetSize().y/2;
    }
    

    glm::vec2 centerPixel;

    switch (anchor)
    {
    case AnchorPoint::TopLeft:       { return  { parentPositionX + CenterAdjustX + Offset.x,                 parentPositionY + windowHeight - CenterAdjustY - Offset.y }; }     break;

    case AnchorPoint::BottomLeft:    { return  { parentPositionX + CenterAdjustX + Offset.x,                 parentPositionY + CenterAdjustY + Offset.y }; }                    break;
                               
    case AnchorPoint::TopRight:      { return  { parentPositionX + windowWidth - CenterAdjustX - Offset.x,   parentPositionY + windowHeight - CenterAdjustY - Offset.y }; }     break;
                            
    case AnchorPoint::BottomRight:   { return  { parentPositionX + windowWidth - CenterAdjustX - Offset.x,   parentPositionY + CenterAdjustY + Offset.y }; }                    break;
                                
    case AnchorPoint::Center:        { return  { parentPositionX + windowWidth/2 + Offset.x,                 parentPositionY + windowHeight/2 + Offset.y }; }                   break;
                          
    case AnchorPoint::TopCenter:     { return  { parentPositionX + windowWidth / 2 + Offset.x,               parentPositionY - CenterAdjustY - Offset.y }; }                     break;
                            
    case AnchorPoint::BottomCenter:  { return  { parentPositionX + windowWidth / 2 + Offset.x,               parentPositionY + CenterAdjustY + Offset.y }; }                    break;

    case AnchorPoint::LeftCenter:    { return  { parentPositionX + CenterAdjustX + Offset.x,                 parentPositionY + windowHeight / 2 + Offset.y }; }                 break;

    case AnchorPoint::RightCenter:   { return  { parentPositionX + windowWidth - CenterAdjustX - Offset.x,   parentPositionY + windowHeight / 2 + Offset.y }; }                 break;
                           
    case AnchorPoint::None:          { return  { parentPositionX + CenterAdjustX + Offset.x,                 parentPositionY + CenterAdjustY + Offset.y }; }                    break;
                          
    default:                         { return  { parentPositionX + windowWidth + CenterAdjustX + Offset.x,   parentPositionY + windowHeight + CenterAdjustY + Offset.y }; }     break;
          
    }
}

glm::vec2 Widget::GetRawAnchorPoint(AnchorPoint anchor, glm::vec2 offset)
{
    float w = Game::GetGame()->GetGameWindow()->GetWindowWidth();
    float h = Game::GetGame()->GetGameWindow()->GetWindowHeight();
    float parentPositionX = 0.0f;
    float parentPositionY = 0.0f;

    if (parent)
    {
        w = parent->GetSize().x;
        h = parent->GetSize().y;
        parentPositionX = parent->GetPosition().x - parent->GetSize().x / 2;
        parentPositionY = parent->GetPosition().y - parent->GetSize().y / 2;
    }

    switch (anchor)
    {
    case AnchorPoint::TopLeft:      return { parentPositionX + offset.x,               parentPositionY + h - offset.y };
    case AnchorPoint::BottomLeft:   return { parentPositionX + offset.x,               parentPositionY + offset.y };
    case AnchorPoint::TopRight:     return { parentPositionX + w - offset.x,           parentPositionY + h - offset.y };
    case AnchorPoint::BottomRight:  return { parentPositionX + w - offset.x,           parentPositionY + offset.y };
    case AnchorPoint::Center:       return { parentPositionX + w * 0.5f + offset.x,    parentPositionY + h * 0.5f + offset.y };
    case AnchorPoint::TopCenter:    return { parentPositionX + w * 0.5f + offset.x,    parentPositionY + h - offset.y };
    case AnchorPoint::BottomCenter: return { parentPositionX + w * 0.5f + offset.x,    parentPositionY + offset.y };
    default:                       return { parentPositionX + offset.x,               parentPositionY + offset.y };
    }
}