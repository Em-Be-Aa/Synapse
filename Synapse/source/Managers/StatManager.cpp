#include "StatManager.h"
#include <GLFW/glfw3.h>
#include <iostream>

StatManager::StatManager()
{
	initialTime = glfwGetTime();
}


void StatManager::Update(double deltaTime)
{
	currentTime = glfwGetTime();
	frameCount++;

	if (enableStats && (currentTime - initialTime >= 1))
	{
		std::cout << "Game Stats------------ " << "FPS: " << frameCount << std::endl;
		std::cout << "Game Stats------------ " << "Draw Calls: " << drawCalls << std::endl;
		frameCount = 0;
		initialTime = currentTime;
	}

	drawCalls = 0;
	
}
