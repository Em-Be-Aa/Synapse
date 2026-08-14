#include "InputManager.h"
#include <iostream>


InputManager::InputManager(GLFWwindow* window) 
{

	InputWindow = window;
	//glfwSetWindowUserPointer(window, this);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);

}


void InputManager::ProcessInputs()
{
	for (auto observer: observers)
	{
		for (auto& inputAction : inputActions)
		{
			if (glfwGetKey(InputWindow, inputAction.first) == GLFW_PRESS && !inputAction.second.wasPressed)
			{
				observer->onInputClicked(inputAction.first);
				inputAction.second.wasPressed = true;
			}

			if (glfwGetKey(InputWindow, inputAction.first) == GLFW_PRESS)
			{
				observer->onInputPressed(inputAction.first);
			}

			if (glfwGetKey(InputWindow, inputAction.first) == GLFW_RELEASE && inputAction.second.wasPressed)
			{
				observer->onInputReleased(inputAction.first);
				inputAction.second.wasPressed = false;
			}
		}
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


