#include "Character.h"
#include "glm/glm.hpp"
#include <iostream>
#include "../Shader/Shader.h"
#include "../Managers/CollisionManager.h"
#include "../Managers/StatManager.h"
#include "../Managers/SynapseFunctionLibrary.h"

// make these hard coded things better
Character::Character() : Collidor(this)
{
    //nlohmann::json Config = SynapseFunctionLibrary::loadJson();

    //std::string path = Config["player"]["animations"]["idle"]["path"].get<std::string>();
    //int frames = Config["player"]["animations"]["idle"]["frames"].get<int>();
    //characterSprite.spriteAnimator.animations["IDLE"] = { path, frames, 1};

    UpdateAnim(IDLE);
}

// Animation system..understand it again and make it a bit cleaner....map is not clean and should be configurable by child classes....also add consistent checks for nullptr if there is a chance
void Character::UpdateAnim(Anim_Mode Mode)
{
    currentAnim = Mode;

    auto It = animMontage.find(currentAnim);
    if (It != animMontage.end())
    {
        Anim_Clip& currentMontage = It->second;
        characterSprite.DefaultImage = currentMontage.spriteSheet;
        characterSprite.spriteAnimator.UpdateUV(currentMontage.imageTiles);
    }

    if (characterSprite.DefaultImage == nullptr)
    {
        std::cout << "Current Sprite Sheet is Null" << std::endl;
        return;
    }
}


void Character::Tick(double deltaTime)
{
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

    if (deltaTime != 0)
    {
        Velocity = (Position - previousPosition) / glm::vec1(deltaTime);
        Speed = glm::length(Velocity);
        previousPosition = Position;

        if (Speed == 0 && currentAnim != IDLE)
        {
            UpdateAnim(IDLE);
        }
        else if(Speed != 0 && currentAnim != WALK)
        {
            UpdateAnim(WALK);
        }
    }
    

    if (characterSprite.DefaultImage == nullptr)
    {
        return;
    }

    RenderComp.model = glm::translate(glm::mat4(1.0f), Position);
    RenderComp.uvScaleOffset = glm::vec4(characterSprite.spriteAnimator.uvScale.x, characterSprite.spriteAnimator.uvScale.y,
                                         characterSprite.spriteAnimator.uvOffset.x, characterSprite.spriteAnimator.uvOffset.y);
    if (characterSprite.DefaultImage)
    {
        RenderComp.textureID = characterSprite.DefaultImage->ID;
    }
}
