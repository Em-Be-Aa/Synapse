#include "../GameConfig/GameConfigs.h"
#include "../Managers/CollisionManager.h"
#include "../Templates/Templates.h"
#include "Character.h"
#include "glm/glm.hpp"
#include <algorithm>
#include <iostream>
#include <memory>

// make these hard coded things better
Character::Character()
{ 
}

void Character::Init()
{
    Collidor = SpawnActor<CollisionComponent>(std::dynamic_pointer_cast<Actor>(shared_from_this()), false, 0.0f);
    RenderComp = SpawnActor<RenderComponent>();
    characterSprite = SpawnActor<Sprite>();
    AbilComp = SpawnActor<AbilityComponent>();
    VitalsComp = SpawnActor<VitalsComponent>();

    RenderComp->SetOwner(shared_from_this());
    AbilComp->SetOwner(std::dynamic_pointer_cast<Character>(shared_from_this()));


    //fix this....this is not clean
   
    // Bind to Collision Delegate(try to find a better way so each class doesn't have to bind in their begin play or constructor....research if this is the only option as Unreal does this too i think.......)
    Collidor->CollisionDelegate.Subscribe
    (
        [this](CollisionInfo Info) {this->OnCollision(Info); }
    );

    VitalsComp->onDeath.Subscribe
    (
        [this]() {this->OnCharacterDeath(); }
    );

    characterSprite->GetAnimator().lock()->onMontageComplete.Subscribe
    (
        [this](std::string Anim) {this->OnAnimationMontageComplete(Anim); }
    );

}


//fix this mess in update and tick
void Character::Tick(double deltaTime)
{

    // Animation Mode Update
    if (deltaTime != 0)
    {
        Velocity = (GetPosition() - GetPreviousPosition()) / glm::vec1(deltaTime);
        Speed = glm::length(Velocity);

        if (Speed == 0 && characterSprite->GetAnimator().lock()->GetCurrentAnim() != "IDLE" && !characterSprite->GetAnimator().lock()->currentMontage.isMontage)
        {
            characterSprite->GetAnimator().lock()->SetCurrentAnim("IDLE", false);
        }
        else if (Speed != 0 && characterSprite->GetAnimator().lock()->GetCurrentAnim() != "WALK" && !characterSprite->GetAnimator().lock()->currentMontage.isMontage)
        {
            characterSprite->GetAnimator().lock()->SetCurrentAnim("WALK", false);

        }
    }
   
    // Send info to render
    RenderComp->defaultQuad.model = glm::translate(glm::mat4(1.0f), GetPosition());
    RenderComp->defaultQuad.textureXFlip = !isFacingRight;
    RenderComp->defaultQuad.uvScaleOffset = glm::vec4(characterSprite->GetAnimator().lock()->uvScale.x, characterSprite->GetAnimator().lock()->uvScale.y,
                                         characterSprite->GetAnimator().lock()->uvOffset.x, characterSprite->GetAnimator().lock()->uvOffset.y);
    if (characterSprite->GetAnimator().lock()->currentMontage.spriteSheet)
    {
        RenderComp->defaultQuad.textureID = characterSprite->GetAnimator().lock()->currentMontage.spriteSheet->ID;
    }
}

void Character::Update(double deltaTime)
{

    // Movement and Collision Update
    movementSpeed = 0.5 * deltaTime;
    movementSpeed = (VitalsComp->GetMomentum() * movementSpeed) + movementSpeed;

    // Collision stuff should happen in collision component....research if giving owner ref to components makes decoupling easier or difficult....
    float halfX = Collidor->BoxSize.x * 0.5f;
    float halfY = Collidor->BoxSize.y * 0.5f;

    // This is wrong....the box is updated always that is why we can escape from collision position...we should be able to escape by reverting the previous delta position...
    // also so many function calls for just getting position
    // but this function in the middle alters the position so just calling one at the start is wrong too so find a better architecture for it.

    glm::vec3 newPosition = GetPosition();

    Collidor->Box.min = { GetPosition().x + deltaPosition.x - halfX, GetPosition().y - halfY};
    Collidor->Box.max = { GetPosition().x + deltaPosition.x + halfX, GetPosition().y  + halfY };

    if (!CollisionManager::GetCollisionManager()->CheckCollision(Collidor))
    {
        glm::vec3 oldPosition = GetPosition();
        newPosition.x = oldPosition.x + deltaPosition.x;
    }
    else
    {
        Collidor->Box.min = { GetPosition().x - halfX, GetPosition().y - halfY };
        Collidor->Box.max = { GetPosition().x + halfX, GetPosition().y + halfY };
    }

    Collidor->Box.min = { GetPosition().x - halfX, GetPosition().y + deltaPosition.y - halfY };
    Collidor->Box.max = { GetPosition().x + halfX, GetPosition().y + deltaPosition.y + halfY };

    if (!CollisionManager::GetCollisionManager()->CheckCollision(Collidor))
    {
        glm::vec3 oldPosition = GetPosition();
        newPosition.y = oldPosition.y + deltaPosition.y;
    }
    else
    {

        Collidor->Box.min = { GetPosition().x - halfX, GetPosition().y - halfY };
        Collidor->Box.max = { GetPosition().x + halfX, GetPosition().y + halfY };
    }

    UpdatePosition(newPosition, false);

    if (deltaPosition.x > 0 && !characterSprite->GetAnimator().lock()->currentMontage.isMontage)
    {
        isFacingRight = true;
    }
    else if (deltaPosition.x < 0 && !characterSprite->GetAnimator().lock()->currentMontage.isMontage)
    {
        isFacingRight = false;
    }

    deltaPosition = { 0.0f, 0.0f, 0.0f };
}

void Character::OnCollision(CollisionInfo Info)
{
    auto iterator = std::find(Info.ignoreActors.begin(), Info.ignoreActors.end(), this);

    auto collidorCharacter = std::dynamic_pointer_cast<Character>(Info.Collidor.lock());

    if ((Info.Collidor.lock() && Info.Collidor.lock().get() == this) || (!Info.ignoreActors.empty() && iterator != Info.ignoreActors.end()) || (collidorCharacter && collidorCharacter->GetFaction() == this->GetFaction()))
    {
        //std::cout << "Ignoring Collision for this actor" << std::endl;
        return;
    }
    
    if (Info.isDamageCollidor)
    {

        // Don't hardcode it, this should come from the ability or attack the character overlapped....
        VitalsComp->TakeDamage(Info.damageCount);

        //std::cout << "Character Base Health left: " << VitalsComp.GetVigor() << std::endl;
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
    characterSprite->GetAnimator().lock()->SetCurrentAnim("DEATH", true);
}

void Character::OnAnimationMontageComplete(std::string Anim)
{
    if (Anim == "DEATH")
    {
        this->Destroy();
    }
}

// everything that we spawn in classes like these where it has its variable an objects that also updates...we need to override and then markpending for destory for its variables too...find a better way...
void Character::Destroy()
{
    Actor::Destroy();

    Collidor->Destroy();

    characterSprite->GetAnimator().lock()->Destroy();
}