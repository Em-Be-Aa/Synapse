#include "Player.h"
#include "glm/glm.hpp"
#include "../Shader/Shader.h"

Player::Player()
{
    // make the player's collision box smaller than the full sprite
    Collidor.BoxSize = glm::vec2(0.3f, 0.3f);
}


void Player::Tick(double deltaTime)
{
    Character::Tick(deltaTime);
}


// Change Input actions from camera to player...camera should follow player
// Make a heirarchy of tick so some objects tick before others always
// Movement when pressing all of diagonal button is faster..make it balanced
void Player::onInputAction(int Key)
{

    // Make movement component of some kind...changing position here and using it in the tick of character does not seem right.....also rendering things are done in character....
    if (Key == GLFW_KEY_D)
    {
        deltaPosition +=(glm::normalize(glm::cross(characterFront, characterUp)) * movementSpeed);
    }
    else if (Key == GLFW_KEY_A)
    {
        deltaPosition -= (glm::normalize(glm::cross(characterFront, characterUp)) * movementSpeed);
    }
    else if (Key == GLFW_KEY_S)
    {
        deltaPosition[1] -= movementSpeed;
    }
    else if (Key == GLFW_KEY_W)
    {
        deltaPosition[1] += movementSpeed;
    }

}