#include "../GameConfig/GameConfigs.h"
#include "Enemy.h"
#include <iostream>
 
Enemy::Enemy()
{

    // this should be cleaner to specify for instances....the collidor box specification specially
    Position = {1.0f, 2.0f, 0.0003f};
    Collidor->BoxSize = glm::vec2(0.2f, 0.3f);

    characterSprite.spriteAnimator->animMontage = GameConfigs::GetGameConfig().GetCharacterData("slime");
    characterSprite.spriteAnimator->SetCurrentAnim("IDLE");
}

void Enemy::Tick(double deltaTime)
{
    Character::Tick(deltaTime);

    //std::cout << "The collision status is: " << Collidor->GetCollisionState() << std::endl;

}
