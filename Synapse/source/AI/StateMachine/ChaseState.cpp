
#include "../../Characters/Character.h"
#include "ChaseState.h"
#include <glm/glm.hpp>
#include <iostream>

void ChaseState::Enter()
{

}

void ChaseState::Update(double deltaTime)
{

    // Make your own formula for good chase....this is all AI
    auto sm = SM.lock();

    if (!sm)
    {
        return;
    }

    auto player =  sm->GetPlayer().lock();
    auto owner = sm->GetOwner().lock();

    if (!player || !owner)
    {
        return;
    }

    glm::vec3 difference = player->GetPosition() - owner->GetPosition();

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
