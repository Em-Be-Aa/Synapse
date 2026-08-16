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

	float GetWindowWidth() { return Width;}
	float GetWindowHeight() { return Height;}

private:
	float Width	= 800.0f;
	float Height = 600.0f;


};

