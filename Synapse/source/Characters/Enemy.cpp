#include "Enemy.h"
#include "Enemy.h"

Enemy::Enemy()
{

    Position = {1.0f, 2.0f, 0.0003f};

    // use default full-size collision box for enemy (can be adjusted)
    Collidor.BoxSize = glm::vec2(0.3f, 0.3f);

    //// Fix this (also why when player is at the same position of enemy a transparent square is shown that covers the enemy)
    animMontage = {
    { IDLE,   Anim_Clip("Assets/Player/Monster/With_Shadows/Monster_Slime_Idle-Sheet.png",			{6, 1}) },
    { WALK,   Anim_Clip("Assets/Player/Monster/With_Shadows/Monster_Slime_Walk-Sheet.png",			{8, 1}) },
    { JUMP,   Anim_Clip("Assets/Player/Monster/With_Shadows/Monster_Slime_Jump_Fall-Sheet.png",		{6, 1}) },
    };
}
