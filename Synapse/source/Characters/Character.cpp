#include "../GameConfig/GameConfigs.h"
#include "../Managers/CollisionManager.h"
#include "Character.h"
#include "glm/glm.hpp"
#include <iostream>

// make these hard coded things better
Character::Character() : Collidor(this)
{
}


void Character::Tick(double deltaTime)
{
    // Movement and Collision Update
    movementSpeed = 1.0 * deltaTime;

    float halfX = Collidor.BoxSize.x * 0.5f;
    float halfY = Collidor.BoxSize.y * 0.5f;
    Collidor.Box.min = { Position.x + deltaPosition.x - halfX, Position.y + deltaPosition.y - halfY };
    Collidor.Box.max = { Position.x + deltaPosition.x + halfX, Position.y + deltaPosition.y + halfY };

    if (!CollisionManager::GetCollisionManager()->CheckCollision(Collidor.Box))
    {
        Position = Position + deltaPosition;
        
    }
    else
    {
        Collidor.Box.min = { Position.x - halfX, Position.y - halfY };
        Collidor.Box.max = { Position.x + halfX, Position.y + halfY };
    }
    deltaPosition = { 0.0f, 0.0f, 0.0f};


    // Animation Mode Update
    if (deltaTime != 0)
    {
        Velocity = (Position - previousPosition) / glm::vec1(deltaTime);
        Speed = glm::length(Velocity);
        previousPosition = Position;

        if (Speed == 0 && characterSprite.spriteAnimator.GetCurrentAnim() != "IDLE" && !characterSprite.spriteAnimator.currentMontage.isMontage)
        {
            characterSprite.spriteAnimator.SetCurrentAnim("IDLE");
        }
        else if (Speed != 0 && characterSprite.spriteAnimator.GetCurrentAnim() != "WALK" && !characterSprite.spriteAnimator.currentMontage.isMontage)
        {
            characterSprite.spriteAnimator.SetCurrentAnim("WALK");

        }
    }
   
    RenderComp.model = glm::translate(glm::mat4(1.0f), Position);
    RenderComp.uvScaleOffset = glm::vec4(characterSprite.spriteAnimator.uvScale.x, characterSprite.spriteAnimator.uvScale.y,
                                         characterSprite.spriteAnimator.uvOffset.x, characterSprite.spriteAnimator.uvOffset.y);
    if (characterSprite.spriteAnimator.currentMontage.spriteSheet)
    {
        RenderComp.textureID = characterSprite.spriteAnimator.currentMontage.spriteSheet->ID;
    }
}
