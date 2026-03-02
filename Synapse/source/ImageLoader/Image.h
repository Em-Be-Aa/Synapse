#pragma once

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"

class Image 
{

public:
	Image(const char* imagePath);

	int width;
	int height;
	int nrChannels;

	unsigned char* Texture;
	unsigned int ID;


private:

	void FreeTexture();

};