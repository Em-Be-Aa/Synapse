#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Window
{

public:

	Window();

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	GLFWwindow* window;

	int Width	= 800;
	int Height	= 600;
};

