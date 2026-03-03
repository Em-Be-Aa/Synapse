#pragma once

#include <GLFW/glfw3.h>
#include <map>
#include <functional>


class InputManager
{
public:

	InputManager(GLFWwindow* window);

	GLFWwindow* InputWindow;

	void BindKey(int Key, std::function<void()> command);

    void ProcessInputs();


private:

    std::map<int, std::function<void()>> inputMap = {
        // --- Movement / Main Letters ---
        { GLFW_KEY_W, []() {} },
        { GLFW_KEY_A, []() {} },
        { GLFW_KEY_S, []() {} },
        { GLFW_KEY_D, []() {} },
        { GLFW_KEY_Q, []() {} },
        { GLFW_KEY_E, []() {} },

        // --- Actions & Modifiers ---
        { GLFW_KEY_SPACE,         []() {} },
        { GLFW_KEY_ESCAPE,        []() {} },
        { GLFW_KEY_ENTER,         []() {} },
        { GLFW_KEY_LEFT_SHIFT,    []() {} },
        { GLFW_KEY_LEFT_CONTROL,  []() {} },
        { GLFW_KEY_TAB,           []() {} },

        // --- Arrows ---
        { GLFW_KEY_UP,    []() {} },
        { GLFW_KEY_DOWN,  []() {} },
        { GLFW_KEY_LEFT,  []() {} },
        { GLFW_KEY_RIGHT, []() {} },

        // --- Mouse Buttons --- (will need a separate map as mouse inputs are handled a bit different)
        //{ GLFW_MOUSE_BUTTON_LEFT,   []() {} },
        //{ GLFW_MOUSE_BUTTON_RIGHT,  []() {} },
        //{ GLFW_MOUSE_BUTTON_MIDDLE, []() {} }
    };
};
