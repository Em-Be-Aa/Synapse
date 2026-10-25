#pragma once

#include "../Actor/Actor.h"
#include "../ImageLoader/Image.h"
#include "Animator.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Sprite : public Object
{

public:
	Sprite();
	Sprite(const char* imagePath);

	void Update(double dT) override {};

	using Object::Init;
	void Init(const char* imagePath);

	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;

private:

	std::shared_ptr<Image> DefaultImage;
	std::shared_ptr<Animator> spriteAnimator;


public:

	std::weak_ptr<Image> GetDefaultImage()
	{
		return DefaultImage;
	}

	std::weak_ptr<Animator> GetAnimator()
	{
		return spriteAnimator;
	}

};

