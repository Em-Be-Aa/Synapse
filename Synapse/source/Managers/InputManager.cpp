#include "InputManager.h"
#include <iostream>


InputManager::InputManager(GLFWwindow* window) 
{

	InputWindow = window;
	glfwSetCursorPosCallback(window, mouse_callback);

}


void InputManager::ProcessInputs()
{
	for (auto& inputAction : inputActions)
	{
		bool isPressed = (inputAction.first == GLFW_MOUSE_BUTTON_1 || inputAction.first == GLFW_MOUSE_BUTTON_2)
			? glfwGetMouseButton(InputWindow, inputAction.first) == GLFW_PRESS
			: glfwGetKey(InputWindow, inputAction.first) == GLFW_PRESS;

		bool wasPressed = inputAction.second.wasPressed;

		bool justClicked = (isPressed && !wasPressed);
		bool justReleased = (!isPressed && wasPressed);

		for (auto observer : observers)
		{
			if (justClicked)
			{
				observer->onInputClicked(inputAction.first);
			}

			if (isPressed)
			{
				observer->onInputPressed(inputAction.first);
			}

			if (justReleased)
			{
				observer->onInputReleased(inputAction.first);
			}
		}

		inputAction.second.wasPressed = isPressed;
	}
}

void InputManager::mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	//InputManager* instance = static_cast<InputManager*>(glfwGetWindowUserPointer(window));

	//if(instance)
	//{
	//	//instance->onMouseMove(xposIn, yposIn);
	//}
}


