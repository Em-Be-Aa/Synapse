#pragma once


class Image 
{

public:

	Image(const char* imagePath);

	int width = 0;
	int height = 0;
	int nrChannels = 0;

	unsigned char* Texture;
	unsigned int ID;


private:

	void FreeTexture();

};