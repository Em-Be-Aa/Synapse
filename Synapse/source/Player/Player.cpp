#include "Player.h"
#include "glm/glm.hpp"
#include "../Shader/Shader.h"

Player::Player(const char* imagePath, Shader* Shader, Camera* Camera) : Character(imagePath, Shader, Camera)
{
    characterShader = Shader;
    characterCamera = Camera;
}


void Player::Tick(double deltaTime)
{
    Position = { characterCamera->cameraPosition.x, characterCamera->cameraPosition.y , 0.0002 };

    Character::Tick(deltaTime);
}
