#pragma once

#include "../Actor/Actor.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../ImageLoader/Image.h"

class Sprite : public Actor
{

public:
    Sprite(const char* imagePath);

    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    Image* DefaultImage;

    void Tick() override;


};

