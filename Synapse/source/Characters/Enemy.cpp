#include "../AI/StateMachine/ChaseState.h"
#include "../GameConfig/GameConfigs.h"
#include "../Templates/Templates.h"
#include "../UI/Game/CharacterHealthBar.h"
#include "Enemy.h"
#include <iostream>
 
Enemy::Enemy(glm::vec3 spawnPosition)
{

    // this should be cleaner to specify for instances....the collidor box specification specially
    Position = spawnPosition;
    Collidor->BoxSize = glm::vec2(0.2f, 0.3f);

    tag = "slime";
    characterFaction = Faction::Enemy;
    characterSprite.spriteAnimator->animMontage = GameConfigs::GetGameConfig().GetCharacterData(tag);
    characterSprite.spriteAnimator->SetCurrentAnim("IDLE", false);

    healthBar = SpawnActor<CharacterHealthBar>(this);


}

void Enemy::Tick(double deltaTime)
{
    Character::Tick(deltaTime);
}

void Enemy::Destroy()
{
    Character::Destroy();

   AIStateMachine->Destroy();
   healthBar->Destroy();
}
