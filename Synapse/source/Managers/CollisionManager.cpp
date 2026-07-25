#include "CollisionManager.h"
#include <iostream>
#include <memory>

CollisionManager* CollisionManager::GetCollisionManager()
{
    std::unique_ptr<CollisionManager> actor(new CollisionManager());
    static CollisionManager* DefaultCollisionManager = actor.get();
    UpdateManager::GetUpdateManager().Register(std::move(actor));
    DefaultCollisionManager->Init();
    return DefaultCollisionManager;
}

void CollisionManager::RegisterCollisionComponent(CollisionComponent* Coll)
{
    CollisionComponents.push_back(Coll);
}

void CollisionManager::Update(double deltaTime)
{

    for (CollisionComponent* Collidor : CollisionComponents)
    {
        CheckCollision(*Collidor);
    }
}

void CollisionManager::CheckCollision(CollisionComponent& Collidor)
{
    for (size_t j = 0; j < CollisionComponents.size(); j++)
    {

        const auto& boxA = Collidor.Box;
        const auto& boxB = CollisionComponents[j]->Box;

        //should make this part of the iscolliding function...
        if (&Collidor == CollisionComponents[j])
        {
            continue;
        }

        if (IsColliding(Collidor.Box, CollisionComponents[j]->Box))
        {
            Collidor.CollisionDelegate.Broadcast({CollisionComponents[j]->GetOwner()});
            Collidor.SetCollisionState(true);
            return;
        }
        else
        {
            Collidor.SetCollisionState(false);
        }
    }

    return;
}
