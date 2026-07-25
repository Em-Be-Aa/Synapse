#include "../GameConfig/GameConfigs.h"
#include "Enemy.h"
#include "Enemy.h"

Enemy::Enemy()
{
    Position = {1.0f, 2.0f, 0.0003f};
    Collidor->BoxSize = glm::vec2(0.2f, 0.3f);

    characterSprite.spriteAnimator->animMontage = GameConfigs::GetGameConfig().GetCharacterData("slime");
    characterSprite.spriteAnimator->SetCurrentAnim("IDLE");
}
