#include "Enemy.h"
#include "Enemy.h"
#include "../GameConfig/GameConfigs.h"

Enemy::Enemy()
{
    Position = {1.0f, 2.0f, 0.0003f};
    Collidor.BoxSize = glm::vec2(0.3f, 0.3f);

    animMontage = GameConfigs::GetGameConfig().GetCharacterData("slime");
    UpdateAnim("IDLE");
}
