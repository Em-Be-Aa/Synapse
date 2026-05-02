#include "InputManager.h"
#include <iostream>


InputManager::InputManager(GLFWwindow* window) 
{

	InputWindow = window;
	glfwSetWindowUserPointer(window, this);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);

}


void InputManager::ProcessInputs()
{
	for (IInputObserver* observer: observers)
	{
		for (int inputAction : inputActions)
		{
			if (glfwGetKey(InputWindow, inputAction) == GLFW_PRESS)
			{
				observer->onInputAction(inputAction);
			}
		}
	}
}

void InputManager::mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	InputManager* instance = static_cast<InputManager*>(glfwGetWindowUserPointer(window));

	if(instance)
	{
		//instance->onMouseMove(xposIn, yposIn);
	}
}


