#include "StatManager.h"
#include "StatManager.h"
#include <GLFW/glfw3.h>
#include <iostream>

StatManager::StatManager()
{
	initialTime = glfwGetTime();
}


void StatManager::Tick()
{
	currentTime = glfwGetTime();
	frameCount++;

	if (currentTime - initialTime >= 1)
	{
		std::cout << "FPS :" << frameCount << std::endl;

		frameCount = 0;
		initialTime = currentTime;
	}
}
