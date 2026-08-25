#include "../GameConfig/GameConfigs.h"
#include "../Managers/CollisionManager.h"
#include "Character.h"
#include "glm/glm.hpp"
#include <algorithm>
#include <iostream>

// make these hard coded things better
Character::Character() : RenderComp(this), HealthComp(this), AbilComp(this)
{ 
    Collidor = SpawnActor<CollisionComponent>(this, false, 0.0f);

    // Bind to Collision Delegate(try to find a better way so each class doesn't have to bind in their begin play or constructor....research if this is the only option as Unreal does this too i think.......)
    Collidor->CollisionDelegate.Subscribe
    (
        [this](CollisionInfo Info){this->OnCollision(Info);}
    );

    HealthComp.onDeath.Subscribe
    (
        [this]() {this->OnCharacterDeath();}
    );

    characterSprite.spriteAnimator->onMontageComplete.Subscribe
    (
        [this](std::string Anim) {this->OnAnimationMontageComplete(Anim);}
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
            characterSprite.spriteAnimator->SetCurrentAnim("IDLE", false);
        }
        else if (Speed != 0 && characterSprite.spriteAnimator->GetCurrentAnim() != "WALK" && !characterSprite.spriteAnimator->currentMontage.isMontage)
        {
            characterSprite.spriteAnimator->SetCurrentAnim("WALK", false);

        }
    }
   
    // Send info to render
    RenderComp.model = glm::translate(glm::mat4(1.0f), Position);
    RenderComp.textureXFlip = !isFacingRight;
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
    Collidor->Box.min = { Position.x + deltaPosition.x - halfX, Position.y  - halfY };
    Collidor->Box.max = { Position.x + deltaPosition.x + halfX, Position.y  + halfY };

    if (!CollisionManager::GetCollisionManager()->CheckCollision(*Collidor))
    {
        Position.x = Position.x + deltaPosition.x;
    }
    else
    {

        Collidor->Box.min = { Position.x - halfX, Position.y - halfY };
        Collidor->Box.max = { Position.x + halfX, Position.y + halfY };
    }

    Collidor->Box.min = { Position.x - halfX, Position.y + deltaPosition.y - halfY };
    Collidor->Box.max = { Position.x + halfX, Position.y + deltaPosition.y + halfY };

    if (!CollisionManager::GetCollisionManager()->CheckCollision(*Collidor))
    {
        Position.y = Position.y + deltaPosition.y;
    }
    else
    {

        Collidor->Box.min = { Position.x - halfX, Position.y - halfY };
        Collidor->Box.max = { Position.x + halfX, Position.y + halfY };
    }

    if (deltaPosition.x > 0 && !characterSprite.spriteAnimator->currentMontage.isMontage)
    {
        isFacingRight = true;
    }
    else if (deltaPosition.x < 0 && !characterSprite.spriteAnimator->currentMontage.isMontage)
    {
        isFacingRight = false;
    }

    deltaPosition = { 0.0f, 0.0f, 0.0f };
}

void Character::OnCollision(CollisionInfo Info)
{
    auto iterator = std::find(Info.ignoreActors.begin(), Info.ignoreActors.end(), this);

    Character* collidorCharacter = dynamic_cast<Character*>(Info.Collidor);

    if ((Info.Collidor && Info.Collidor == this) || (!Info.ignoreActors.empty() && iterator != Info.ignoreActors.end()) || (collidorCharacter && collidorCharacter->GetFaction() == this->GetFaction()))
    {
        //std::cout << "Ignoring Collision for this actor" << std::endl;
        return;
    }
    
    if (Info.isDamageCollidor)
    {

        // Don't hardcode it, this should come from the ability or attack the character overlapped....
        HealthComp.TakeDamage(Info.damageCount);

        //std::cout << "Character Base Health left: " << HealthComp.GetBaseHealth() << std::endl;
        //std::cout << "Character Armor Health left: " << HealthComp.GetArmorHealth() << std::endl;

    }
    else
    {
        //std::cout << "Collided with another object in the world" << std::endl;
    }
}

void Character::OnCharacterDeath()
{
    std::cout << "Character is dead" << std::endl;

    // Alive Status is added so during death animations AI state machine dont work and attack and damage the player. Research if this is necessary or is there a better way.
    SetAliveStatus(false);
    characterSprite.spriteAnimator->SetCurrentAnim("DEATH", true);
}

void Character::OnAnimationMontageComplete(std::string Anim)
{
    if (Anim == "DEATH")
    {
        //std::cout << "Death Animation is complete" << std::endl;
        this->Destroy();
    }
}

// everything that we spawn in classes like these where it has its variable an objects that also updates...we need to override and then markpending for destory for its variables too...find a better way...
void Character::Destroy()
{
    Actor::Destroy();

    Collidor->Destroy();

    characterSprite.spriteAnimator->Destroy();
}