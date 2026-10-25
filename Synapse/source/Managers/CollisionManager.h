#pragma once
#include "../Actor/Object.h"
#include "../Collision/CollisionComponent.h"
#include <vector>


class CollisionManager : public Object
{

public:


	void RegisterCollisionComponent(std::weak_ptr<CollisionComponent> Coll);
	void UnregisterCollisionComponent(std::weak_ptr<CollisionComponent> Coll);
	void Update(double deltaTime) override;
	static CollisionManager* GetCollisionManager();
	bool CheckCollision(std::weak_ptr<CollisionComponent> SourceCollidor);
	bool IsColliding(const CollisionBox& A, const CollisionBox& B)
	{
		return	A.min.x <= B.max.x &&
				A.max.x >= B.min.x &&
				A.min.y <= B.max.y &&
				A.max.y >= B.min.y;
	};

	void DestoryPendingCollidors()
	{
		std::erase_if(CollisionComponents, [](std::weak_ptr<CollisionComponent> CC) 
			{
				if (CC.lock())
				{
					return CC.lock()->isPendingDestroy;
				}
				else
				{
					return true;
				}
			});
	};

private:
	std::vector<std::weak_ptr<CollisionComponent>> CollisionComponents;
	CollisionManager() {};
};

