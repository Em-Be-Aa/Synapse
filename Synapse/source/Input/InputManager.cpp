#include "InputManager.h"


InputManager::InputManager(GLFWwindow* window) 
{

	InputWindow = window;
	glfwSetWindowUserPointer(window, this);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);

}

void InputManager::BindKey(int Key, std::function<void()> command)
{

	inputMap[Key] = command;

}

void InputManager::ProcessInputs()
{

	for(const auto& keyValuePair : inputMap) 
	{
		if (glfwGetKey(InputWindow, keyValuePair.first) == GLFW_PRESS)
		{
			keyValuePair.second();
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


