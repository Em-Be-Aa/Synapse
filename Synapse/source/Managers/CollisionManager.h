#pragma once
#include <vector>
#include "../Actor/Object.h"
#include "../Collision/CollisionComponent.h"


class CollisionManager : public Object
{

public:


	void RegisterCollisionComponent(CollisionComponent* Coll);
	void Tick(double deltaTime) override;
	static CollisionManager* GetCollisionManager();
	bool CheckCollision(const CollisionBox& movingObject);
	bool IsColliding(const CollisionBox& A, const CollisionBox& B)
	{
		return	A.min.x < B.max.x &&
				A.max.x > B.min.x &&
				A.min.y < B.max.y &&
				A.max.y > B.min.y;
	};

private:
	std::vector<CollisionComponent*> CollisionComponents;
	CollisionManager() {};
};

