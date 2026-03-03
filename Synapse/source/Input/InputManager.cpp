#include "InputManager.h"


InputManager::InputManager(GLFWwindow* window) 
{

	InputWindow = window;

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


