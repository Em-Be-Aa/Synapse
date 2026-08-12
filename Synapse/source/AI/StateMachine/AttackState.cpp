#include "../../Characters/Character.h"
#include "AttackState.h"
#include <glm/glm.hpp>

void AttackState::Enter()
{

}

void AttackState::Update(double deltaTime)
{
    SM->GetOwner()->GetAbilityComponent().ActivateAbility("LIGHT ATTACK");
}

void AttackState::Exit()
{

}
