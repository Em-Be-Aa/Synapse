#include "../../Game/Game.h"
#include "../../Managers/InputManager.h"
#include "../../Window/Window.h"
#include "Button.h"

void Button::Init()
{
    Game::GetGame()->GetInputManager()->EnableActorInput(this);
}
void Button::Update(double dT)
{
    Widget::Update(dT);

    glm::vec2 cursor = Game::GetGame()->GetGameWindow()->GetCursorPosition();
    glm::vec2 halfSize = GetSize() * 0.5f;


    currentlyOver =
        cursor.x >= widgetPosition.x - halfSize.x &&
        cursor.x <= widgetPosition.x + halfSize.x &&
        cursor.y >= widgetPosition.y - halfSize.y &&
        cursor.y <= widgetPosition.y + halfSize.y;

    if (currentlyOver && !isHovered)
    {
        isHovered = true;
        SetSize({ GetSize().x + 10.0f, GetSize().y + 10.0f });
        OnHovered.Broadcast();
    }
    else if (!currentlyOver && isHovered)
    {
        isHovered = false;
        SetSize({ GetSize().x - 10.0f, GetSize().y - 10.0f });
        OnUnhovered.Broadcast();
    }
}

void Button::onInputPressed(int Key)
{
}

void Button::onInputClicked(int Key)
{
    // Log every time the function receives an input, showing the key code and hover state
    std::cout << "[Button] onInputClicked triggered | Key: " << Key
        << " | currentlyOver: " << (currentlyOver ? "True" : "False") << std::endl;

    if (currentlyOver && Key == GLFW_MOUSE_BUTTON_1)
    {
        std::cout << "[Button] Valid left-click detected. Broadcasting OnClicked." << std::endl;
        OnClicked.Broadcast();
    }
}

void Button::onInputReleased(int Key)
{
}
