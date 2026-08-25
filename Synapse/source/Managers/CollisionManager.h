#pragma once
#include "../Actor/Object.h"
#include "../Collision/CollisionComponent.h"
#include <vector>


class CollisionManager : public Object
{

public:


	void RegisterCollisionComponent(CollisionComponent* Coll);
	void UnregisterCollisionComponent(CollisionComponent* Coll);
	void Update(double deltaTime) override;
	static CollisionManager* GetCollisionManager();
	bool CheckCollision(CollisionComponent& SourceCollidor);
	bool IsColliding(const CollisionBox& A, const CollisionBox& B)
	{
		return	A.min.x <= B.max.x &&
				A.max.x >= B.min.x &&
				A.min.y <= B.max.y &&
				A.max.y >= B.min.y;
	};

	void DestoryPendingCollidors()
	{
		std::erase_if(CollisionComponents, [](const CollisionComponent* CC) { return CC->isPendingDestroy; });
	};

private:
	std::vector<CollisionComponent*> CollisionComponents;
	CollisionManager() {};
};

