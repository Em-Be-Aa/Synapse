#include "Player.h"
#include "glm/glm.hpp"
#include "../Shader/Shader.h"

Player::Player(const char* imagePath, Shader* Shader) : Character(imagePath, Shader)
{
    characterShader = Shader;
}


void Player::Tick(double deltaTime)
{
    Character::Tick(deltaTime);
}


// Change Input actions from camera to player...camera should follow player
void Player::onInputAction(int Key)
{
    if (Key == GLFW_KEY_W)
    {
        Position[1] = Position[1] +  movementSpeed;
    }
    else if (Key == GLFW_KEY_A)
    {
        Position -= glm::normalize(glm::cross(characterFront, characterUp)) * movementSpeed;
    }
    else if (Key == GLFW_KEY_S)
    {
        Position[1] = Position[1] - movementSpeed;
    }
    else if (Key == GLFW_KEY_D)
    {
        Position += glm::normalize(glm::cross(characterFront, characterUp)) * movementSpeed;
    }
}