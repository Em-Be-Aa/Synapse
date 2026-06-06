#include "Sprite.h"

Sprite::Sprite()
{
	float vertices[] = {
   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom Left
	0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // Bottom Right
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // Top Right
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // Top Right
   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // Top Left
   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom Left
	};

	unsigned int indices[] =
	{
		0,  1,  2,
		3,  4,  5,
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

// We need some rendering stuff separate it is mingled with the logic rn 
Sprite::Sprite(const char* imagePath)
{
	float vertices[] = {
   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom Left
	0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // Bottom Right
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // Top Right
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // Top Right
   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // Top Left
   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom Left
	};

	unsigned int indices[] =
	{
		0,  1,  2,
		3,  4,  5, 
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	DefaultImage = new Image(imagePath);

}
