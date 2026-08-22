#include "../../Game/Game.h"
#include "../../Shader/Renderer2D.h"
#include "../../Text/stb_truetype.h"
#include "../../Window/Window.h"
#include "TextWidget.h"
#include <glm/ext/matrix_transform.hpp>

TextWidget::TextWidget(Font* font, std::string initialText, glm::vec4 Color, glm::vec2 Size, glm::vec2 offset)
    : Widget(Size, offset), fontRef(font), text(initialText)
{
    widgetColor = Color;
}

void TextWidget::Update(double dT)
{
    if (!fontRef || text.empty())
        return;

    float windowWidth = Game::GetGame()->GetGameWindow()->GetWindowWidth();
    float windowHeight = Game::GetGame()->GetGameWindow()->GetWindowHeight();

    glm::vec2 anchorPoint = GetRawAnchorPoint(widgetAnchor, offset);

    float totalWidth = 0.0f;
    for (char c : text)
    {
        if (c < 32 || c > 127) continue;
        totalWidth += fontRef->GetBakedChars()[c - 32].xadvance;
    }

    bool isRightAnchored = (widgetAnchor == AnchorPoint::TopRight || widgetAnchor == AnchorPoint::BottomRight);
    bool isTopAnchored = (widgetAnchor == AnchorPoint::TopLeft || widgetAnchor == AnchorPoint::TopRight);
    float ascentEstimate = fontRef->GetPixelHeight() * 0.35f;

    float cursorX = isRightAnchored ? anchorPoint.x - totalWidth : anchorPoint.x;
    float cursorY = isTopAnchored ? anchorPoint.y - ascentEstimate : anchorPoint.y + ascentEstimate;

    RenderComp.textureID = fontRef->GetTextureID();
    RenderComp.tint = widgetColor;
    RenderComp.space = RenderSpace::Screen;

    for (char c : text)
    {
        if (c < 32 || c > 127) continue; // outside baked range, skip

        stbtt_aligned_quad quad;
        stbtt_GetBakedQuad(
            (stbtt_bakedchar*)fontRef->GetBakedChars(),
            fontRef->GetAtlasWidth(), fontRef->GetAtlasHeight(),
            c - 32,
            &cursorX, &cursorY,
            &quad,
            1
        );

        float glyphWidth = quad.x1 - quad.x0;
        float glyphHeight = quad.y1 - quad.y0;
        glm::vec2 glyphCenter = { quad.x0 + glyphWidth * 0.5f, quad.y0 + glyphHeight * 0.5f };

        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(glyphCenter, 0.0f));
        model = glm::scale(model, glm::vec3(glyphWidth, glyphHeight, 1.0f)); // positive, no flip here

        glm::vec2 uvScale = { quad.s1 - quad.s0, -(quad.t1 - quad.t0) }; // negate V scale
        glm::vec2 uvOffset = { quad.s0, quad.t1 };

        RenderComp.model = model;
        RenderComp.uvScaleOffset = glm::vec4(uvScale, uvOffset);
        RenderComp.layer = zOrder;
        Renderer2D::GetRenderer()->Submit(RenderComp);
    }
}