#include "../Characters/Character.h"
#include "../Templates/Templates.h"
#include "CollisionManager.h"
#include <memory>

CollisionManager* CollisionManager::GetCollisionManager()
{
    static std::shared_ptr<CollisionManager> DefaultCollisionManager;

    if (!DefaultCollisionManager)
    {
        DefaultCollisionManager = std::shared_ptr<CollisionManager>(new CollisionManager());
        UpdateManager::GetUpdateManager().RegisterPostUpdateObject(DefaultCollisionManager);
        DefaultCollisionManager->Init();
    }

    return DefaultCollisionManager.get();
}

void CollisionManager::RegisterCollisionComponent(std::weak_ptr<CollisionComponent> Coll)
{
    CollisionComponents.push_back(Coll);
}

void CollisionManager::UnregisterCollisionComponent(std::weak_ptr<CollisionComponent> Coll)
{
    std::erase_if(CollisionComponents, [Coll](const std::weak_ptr<CollisionComponent>& weak)
        {
            return Coll.lock() == weak.lock();
        });
}


void CollisionManager::Update(double deltaTime)
{
    for (auto Collidor : CollisionComponents)
    {
        CheckCollision(Collidor);
    }
}

bool CollisionManager::CheckCollision(std::weak_ptr<CollisionComponent> Source)
{
    auto SourceCollidor = Source.lock();

    if (!SourceCollidor)
    {
        return false;
    }

    std::vector<std::weak_ptr<CollisionComponent>> currentCollidors = {};

    for (size_t j = 0; j < CollisionComponents.size(); j++)
    {
        auto OtherCollidor = CollisionComponents[j].lock();
        if (!OtherCollidor)
        {
            continue;
        }

        const auto& boxA = SourceCollidor->Box;
        const auto& boxB = OtherCollidor->Box;

        auto sourceCollidorOwner = dynamic_pointer_cast<Character>(SourceCollidor->GetOwner().lock());
        auto otherCollidorOwner = dynamic_pointer_cast<Character>(OtherCollidor->GetOwner().lock());

        //should make this part of the iscolliding function...
        if (SourceCollidor == OtherCollidor || sourceCollidorOwner->GetFaction() == otherCollidorOwner->GetFaction())
        {
            continue;
        }

        //remember to learn if there are 40 instances of collidor and you want to see the memory or variable of a single specific one how to do that....
        if (IsColliding(boxA, boxB))
        {
            currentCollidors.push_back(OtherCollidor);

            // This will fire once on overlap
            if (!SourceCollidor->IsCurrentCollidor(OtherCollidor))
            {
                SourceCollidor->CollisionDelegate.Broadcast({OtherCollidor->GetOwner(), OtherCollidor->isDamageCollidor, OtherCollidor->damageCount,{} });
                if (OtherCollidor->isDamageCollidor)
                {
                    std::cout << "Damage done to character" << std::endl;
                }
            }
        }
    }

    SourceCollidor->UpdateCollidors(currentCollidors);

    return SourceCollidor->GetCollisionState();
}
