
#include "../../Characters/Character.h"
#include "ChaseState.h"
#include <glm/glm.hpp>

void ChaseState::Enter()
{

}

void ChaseState::Update(double deltaTime)
{

    // Make your own formula for good chase....this is all AI
    Character* player =  SM->GetPlayer();
    Character* owner = SM->GetOwner();


    glm::vec3 difference = player->Position - owner->Position;

    float distance = glm::length(difference);

    float stepSize = 0.01f;

    if (!(distance <= stepSize))
    {
        glm::vec3 direction = difference / distance;
        owner->SetDeltaPosition(direction * stepSize);
    }


}

void ChaseState::Exit()
{

}
