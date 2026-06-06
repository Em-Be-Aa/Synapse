#include "CollisionManager.h"
#include <iostream>

CollisionManager* CollisionManager::GetCollisionManager()
{
    static CollisionManager DefaultCollisionManager;
    return &DefaultCollisionManager;
}

void CollisionManager::RegisterCollisionComponent(CollisionComponent* Coll)
{
    CollisionComponents.push_back(Coll);
    std::cout << "Collision Component Registered" << std::endl;
}

void CollisionManager::Tick(double deltaTime)
{
    //for (size_t i = 0; i < CollisionComponents.size(); i++)
    //{
    //    CollisionComponents[i]->isColliding = false;
    //}

    //for (size_t i = 0; i < CollisionComponents.size(); i++)
    //{
    //    
    //    for (size_t j = i + 1; j < CollisionComponents.size(); j++)
    //    {

    //        const auto& boxA = CollisionComponents[i]->Box;
    //        const auto& boxB = CollisionComponents[j]->Box;

    //        // 2. Break down the actual overlap math so you can see it
    //        bool overlapX = boxA.max.x >= boxB.min.x && boxB.max.x >= boxA.min.x;
    //        bool overlapY = boxA.max.y >= boxB.min.y && boxB.max.y >= boxA.min.y;

    //        // 3. Print the elaborate diagnostic block
    //        std::cout << "==========================================\n";
    //        std::cout << "Checking Pair: Obj[" << i << "] vs Obj[" << j << "]\n";
    //        std::cout << "------------------------------------------\n";
    //        std::cout << "Obj[" << i << "] Min: (" << boxA.min.x << ", " << boxA.min.y << ") | Max: (" << boxA.max.x << ", " << boxA.max.y << ")\n";
    //        std::cout << "Obj[" << j << "] Min: (" << boxB.min.x << ", " << boxB.min.y << ") | Max: (" << boxB.max.x << ", " << boxB.max.y << ")\n";
    //        std::cout << "------------------------------------------\n";
    //        std::cout << "X-Axis Overlap: " << (overlapX ? "YES" : "NO ") << "\n";
    //        std::cout << "Y-Axis Overlap: " << (overlapY ? "YES" : "NO ") << "\n";
    //        std::cout << "Final Verdict : " << ((overlapX && overlapY) ? ">>> COLLIDING <<<" : "Clear") << "\n";
    //        std::cout << "==========================================\n\n";
    //        if (IsColliding(CollisionComponents[i]->Box, CollisionComponents[j]->Box))
    //        {
    //            CollisionComponents[i]->isColliding = true;
    //            break;
    //        };
    //    }
    //}
}

bool CollisionManager::CheckCollision(const CollisionBox& movingObject)
{
    for (size_t j = 0; j < CollisionComponents.size(); j++)
    {

        const auto& boxA = movingObject;
        const auto& boxB = CollisionComponents[j]->Box;

        if (boxA.max == boxB.max && boxA.min == boxB.min)
        {
            continue;
        }

        if (IsColliding(movingObject, CollisionComponents[j]->Box))
        {
            return true;
        };
    }

    return false;
}
