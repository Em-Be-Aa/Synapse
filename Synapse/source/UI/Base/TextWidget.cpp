#include "../../Game/Game.h"
#include "../../Shader/Renderer2D.h"
#include "../../Text/stb_truetype.h"
#include "../../Window/Window.h"
#include "TextWidget.h"
#include <glm/ext/matrix_transform.hpp>

TextWidget::TextWidget(Font* font, std::string initialText) : fontRef(font), text(initialText)
{

}

TextWidget::TextWidget(Font* font, std::string initialText, Widget* Parent) : fontRef(font), text(initialText)
{
    parent = Parent;
}

void TextWidget::Update(double dT)
{
    if (!fontRef || text.empty())
        return;

    glm::vec2 anchorPoint = GetRawAnchorPoint(widgetAnchor, offset);

    float totalWidth = 0.0f;
    for (char c : text)
    {
        if (c < 32 || c > 127) continue;
        totalWidth += fontRef->GetBakedChars()[c - 32].xadvance;
    }

    bool isRightAnchored = (widgetAnchor == AnchorPoint::TopRight || widgetAnchor == AnchorPoint::BottomRight);
    bool isHCenterAnchored = (widgetAnchor == AnchorPoint::Center || widgetAnchor == AnchorPoint::TopCenter || widgetAnchor == AnchorPoint::BottomCenter);

    bool isTopAnchored = (widgetAnchor == AnchorPoint::TopLeft || widgetAnchor == AnchorPoint::TopRight || widgetAnchor == AnchorPoint::TopCenter);
    bool isBottomAnchored = (widgetAnchor == AnchorPoint::BottomLeft || widgetAnchor == AnchorPoint::BottomRight || widgetAnchor == AnchorPoint::BottomCenter);
    bool isVCenterAnchored = (widgetAnchor == AnchorPoint::Center);

    float ascent = fontRef->GetAscentPixels();
    float descent = fontRef->GetDescentPixels();

    float cursorX = isRightAnchored ? anchorPoint.x - totalWidth
        : isHCenterAnchored ? anchorPoint.x - totalWidth * 0.5f
        : anchorPoint.x;

    float cursorY;

    if (isVCenterAnchored)
    {
        // Measurement pass: find the real visual top/bottom of THIS string,
        // not the font's theoretical max ascent/descent.
        float measureX = 0.0f, measureY = 0.0f;
        float visualTop = 0.0f, visualBottom = 0.0f;
        bool first = true;

        for (char c : text)
        {
            if (c < 32 || c > 127) continue;
            stbtt_aligned_quad q;
            stbtt_GetBakedQuad((stbtt_bakedchar*)fontRef->GetBakedChars(),
                fontRef->GetAtlasWidth(), fontRef->GetAtlasHeight(),
                c - 32, &measureX, &measureY, &q, 1);

            if (first) { visualTop = q.y0; visualBottom = q.y1; first = false; }
            else { visualTop = std::min(visualTop, q.y0); visualBottom = std::max(visualBottom, q.y1); }
        }

        float centerOffset = (visualTop + visualBottom) * 0.5f; // offset from baseline, y-down
        cursorY = anchorPoint.y + centerOffset;
    }
    else
    {
        cursorY = isTopAnchored ? anchorPoint.y - ascent
            : isBottomAnchored ? anchorPoint.y + descent
            : anchorPoint.y;
    }

    const float baselineY = cursorY;

    RenderComp.textureID = fontRef->GetTextureID();
    RenderComp.tint = widgetColor;
    RenderComp.space = RenderSpace::Screen;

    for (char c : text)
    {
        if (c < 32 || c > 127) continue;

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

        float glyphCenterYDown = quad.y0 + glyphHeight * 0.5f;
        float glyphCenterYUp = (2.0f * baselineY) - glyphCenterYDown;

        glm::vec2 glyphCenter = { quad.x0 + glyphWidth * 0.5f, glyphCenterYUp };

        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(glyphCenter, 0.0f));
        model = glm::scale(model, glm::vec3(glyphWidth, glyphHeight, 1.0f));

        glm::vec2 uvScale = { quad.s1 - quad.s0, -(quad.t1 - quad.t0) };
        glm::vec2 uvOffset = { quad.s0, quad.t1 };

        RenderComp.model = model;
        RenderComp.uvScaleOffset = glm::vec4(uvScale, uvOffset);
        RenderComp.layer = zOrder;
        RenderComp.SetIsDisabled(!isVisible);

        Renderer2D::GetRenderer()->Submit(RenderComp);
    }
}