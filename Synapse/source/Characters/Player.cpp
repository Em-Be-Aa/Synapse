#include "../Game/Game.h"
#include "../Game/Game.h"
#include "../GameConfig/GameConfigs.h"
#include "../Templates/Templates.h"
#include "../Window/Window.h"
#include "Abilities/AttackAbility.h"
#include "Abilities/DashAbility.h"
#include "glm/glm.hpp"
#include "Player.h"
#include <iostream>
#include <memory>
#include <string>

Player::Player()
{
    // make the player's collision box smaller than the full sprite
    


  }


void Player::Init()
{
    Character::Init();

    Collidor->BoxSize = glm::vec2(0.2f, 0.3f);

    tag = "player";
    characterFaction = Faction::Player;
    characterSprite->GetAnimator().lock()->animMontage = GameConfigs::GetGameConfig().GetCharacterData(tag);
    characterSprite->GetAnimator().lock()->SetCurrentAnim("IDLE", false);

    AbilityInfo LightAttack = GameConfigs::GetGameConfig().GetCharacterAbilityData(tag, "LIGHT ATTACK");
    AbilityInfo HeavyAttack = GameConfigs::GetGameConfig().GetCharacterAbilityData(tag, "HEAVY ATTACK");
    AbilityInfo Dash = GameConfigs::GetGameConfig().GetCharacterAbilityData(tag, "DASH");

    AddAbility<AttackAbility>(std::static_pointer_cast<Character>(shared_from_this()), "LIGHT ATTACK", LightAttack);
    AddAbility<AttackAbility>(std::static_pointer_cast<Character>(shared_from_this()), "HEAVY ATTACK", HeavyAttack);
    AddAbility<DashAbility>(std::static_pointer_cast<Character>(shared_from_this()), "DASH", Dash);

    if (auto VC = GetVitalsComponent().lock())
    {
        VC->SetVitals({ {100.0f, 100.0f }, 0.0f, {50.0f, 50.0f}, 0.0f, 0.0f, 0, {"LIGHT ATTACK", LightAttack.abilityDamage, LightAttack.abilityCooldown }, {"HEAVY ATTACK", HeavyAttack.abilityDamage, HeavyAttack.abilityCooldown }, {"DASH", Dash.abilityDamage, Dash.abilityCooldown, Dash.dashDistance } });
    }

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
        AbilComp->ActivateAbility("LIGHT ATTACK");
    }
    else if (Key == GLFW_KEY_Q)
    {
        AbilComp->ActivateAbility("HEAVY ATTACK");
    }
    else if (Key == GLFW_KEY_SPACE)
    {
        AbilComp->ActivateAbility("DASH");
    }

    if (Key == GLFW_KEY_ESCAPE)
    {
        if (auto gameWindow = Game::GetGame()->GetGameWindow().lock())
        {
            glfwSetWindowShouldClose(gameWindow->window, GLFW_TRUE);
        }
    }

}


void Player::onInputReleased(int Key)
{

}
