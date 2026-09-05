#pragma once

#include "../../Text/Font.h"
#include "Widget.h"
#include <string>

class TextWidget : public Widget
{
public:
    TextWidget(Font* font, std::string initialText);
    TextWidget(Font* font, std::string initialText, Widget* Parent);

    void Update(double dT) override;

    void SetText(const std::string& newText) { text = newText; }

private:

    Font* fontRef;
    std::string text;
};