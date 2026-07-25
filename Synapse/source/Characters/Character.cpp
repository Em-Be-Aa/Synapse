#include "../GameConfig/GameConfigs.h"
#include "Character.h"
#include "glm/glm.hpp"
#include <iostream>

// make these hard coded things better
Character::Character()
{ 

    Collidor = SpawnActor<CollisionComponent>();

    // Bind to Collision Delegate(try to find a better way so each class doesn't have to bind in their begin play or constructor....research if this is the only option as Unreal does this too i think.......)
    Collidor->CollisionDelegate.Subscribe
    (
        [this](CollisionInfo Info){this->OnCollision(Info);}
    );
}

//fix this mess in update and tick
void Character::Tick(double deltaTime)
{

    // Animation Mode Update
    if (deltaTime != 0)
    {
        Velocity = (Position - previousPosition) / glm::vec1(deltaTime);
        Speed = glm::length(Velocity);
        previousPosition = Position;

        if (Speed == 0 && characterSprite.spriteAnimator->GetCurrentAnim() != "IDLE" && !characterSprite.spriteAnimator->currentMontage.isMontage)
        {
            characterSprite.spriteAnimator->SetCurrentAnim("IDLE");
        }
        else if (Speed != 0 && characterSprite.spriteAnimator->GetCurrentAnim() != "WALK" && !characterSprite.spriteAnimator->currentMontage.isMontage)
        {
            characterSprite.spriteAnimator->SetCurrentAnim("WALK");

        }
    }
   
    // Send info to render
    RenderComp.model = glm::translate(glm::mat4(1.0f), Position);
    RenderComp.uvScaleOffset = glm::vec4(characterSprite.spriteAnimator->uvScale.x, characterSprite.spriteAnimator->uvScale.y,
                                         characterSprite.spriteAnimator->uvOffset.x, characterSprite.spriteAnimator->uvOffset.y);
    if (characterSprite.spriteAnimator->currentMontage.spriteSheet)
    {
        RenderComp.textureID = characterSprite.spriteAnimator->currentMontage.spriteSheet->ID;
    }
}

void Character::Update(double deltaTime)
{

    // Movement and Collision Update
    movementSpeed = 1.0 * deltaTime;

    // Collision stuff should happen in collision component....research if giving owner ref to components makes decoupling easier or difficult....
    float halfX = Collidor->BoxSize.x * 0.5f;
    float halfY = Collidor->BoxSize.y * 0.5f;

    // This is wrong....the box is updated always that is why we can escape from collision position...we should be able to escape by reverting the previous delta position...
    Collidor->Box.min = { Position.x + deltaPosition.x - halfX, Position.y + deltaPosition.y - halfY };
    Collidor->Box.max = { Position.x + deltaPosition.x + halfX, Position.y + deltaPosition.y + halfY };

    if (!Collidor->isColliding)
    {
        //std::cout << "Character is not colliding so movement can be added" << std::endl;

        Position = Position + deltaPosition;
    }

    deltaPosition = { 0.0f, 0.0f, 0.0f };
}

void Character::OnCollision(CollisionInfo Info)
{
    

    //deltaPosition = { 0.0f, 0.0f, 0.0f };
}
