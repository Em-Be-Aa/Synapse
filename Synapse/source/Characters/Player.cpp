#include "../GameConfig/GameConfigs.h"
#include "../Shader/Shader.h"
#include "glm/glm.hpp"
#include "Player.h"
#include <iostream>

Player::Player()
{
    // make the player's collision box smaller than the full sprite
    Collidor.BoxSize = glm::vec2(0.3f, 0.3f);

    // Do all config in the game class not all player will need to load the same config...
    characterSprite.spriteAnimator.animMontage = GameConfigs::GetGameConfig().GetCharacterData("player");
    characterSprite.spriteAnimator.SetCurrentAnim("IDLE");
}


void Player::Tick(double deltaTime)
{
    Character::Tick(deltaTime);
}


// Change Input actions from camera to player...camera should follow player
// Make a heirarchy of tick so some objects tick before others always
// Movement when pressing all of diagonal button is faster..make it balanced
void Player::onInputPressed(int Key)
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


void Player::onInputClicked(int Key)
{
    if (Key == GLFW_KEY_E)
    {
        std::cout << "This works beleive me" << std::endl;
        AbilComp.ActivateAbility("LIGHT ATTACK");
    }
    else if (Key == GLFW_KEY_Q)
    {
        std::cout << "This works beleive me" << std::endl;
        AbilComp.ActivateAbility("HEAVY ATTACK");
        //characterSprite.spriteAnimator.SetCurrentAnim("HEAVY ATTACK");
    }
}


void Player::onInputReleased(int Key)
{

}
