#pragma once

#include "../../Text/Font.h"
#include "Widget.h"
#include <string>

class TextWidget : public Widget
{
public:
    TextWidget(std::weak_ptr<Font> font, std::string initialText);
    TextWidget(std::weak_ptr<Font> font, std::string initialText, std::weak_ptr<Widget> Parent);

    void Update(double dT) override;

    void SetText(const std::string& newText) { text = newText; }

private:

    std::weak_ptr<Font> fontRef;
    std::string text;
};