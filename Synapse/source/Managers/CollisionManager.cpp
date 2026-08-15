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

void CollisionManager::UnregisterCollisionComponent(CollisionComponent* Coll)
{
    std::erase(CollisionComponents, Coll);
}

void CollisionManager::Update(double deltaTime)
{

    for (CollisionComponent* Collidor : CollisionComponents)
    {
        CheckCollision(*Collidor);
    }
}

void CollisionManager::CheckCollision(CollisionComponent& SourceCollidor)
{

    std::vector<CollisionComponent*> currentCollidors = {};

    for (size_t j = 0; j < CollisionComponents.size(); j++)
    {
        auto OtherCollidor = CollisionComponents[j];

        const auto& boxA = SourceCollidor.Box;
        const auto& boxB = OtherCollidor->Box;

        //should make this part of the iscolliding function...
        if (&SourceCollidor == OtherCollidor)
        {
            continue;
        }

        //remember to learn if there are 40 instances of collidor and you want to see the memory or variable of a single specific one how to do that....
        if (IsColliding(boxA, boxB))
        {
            currentCollidors.push_back(OtherCollidor);

            // This will fire once on overlap
            if (!SourceCollidor.IsCurrentCollidor(OtherCollidor))
            {
                SourceCollidor.CollisionDelegate.Broadcast({OtherCollidor->GetOwner(), OtherCollidor->isDamageCollidor, OtherCollidor->damageCount,{} });
            }
        }
    }

    SourceCollidor.UpdateCollidors(currentCollidors);

    return;
}
