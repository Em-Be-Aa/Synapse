#pragma once

#include "../Actor/Object.h"
#include "../Enums&Structs/GameTypes.h"
#include "../Shader/RenderComponent.h"
#include "../Shader/Shader.h"
#include "../Sprite/Sprite.h"
#include <glm/glm.hpp>


class CollisionComponent : public Object
{

public:
	CollisionComponent(std::weak_ptr<Actor> Owner);
	CollisionComponent(bool isDamage, float damageAmount);
	CollisionComponent(std::weak_ptr<Actor> Owner, bool isDamage, float damageAmount);
	~CollisionComponent();

	void Init() override;
	// This is component of an actor...think about if this need tick or update....this goes for all components...the initial thought was to use update for managers, components so their logic runs before actors run tick
	void Update(double deltaTime) override;

	CollisionBox Box;
	bool isColliding = false;
	glm::vec2 BoxSize = glm::vec2(1.0f, 1.0f);
	bool isDamageCollidor = false;
	float damageCount = 0.0f;

	Delegate<CollisionInfo> CollisionDelegate;


private:

	std::shared_ptr<Sprite> collisionSprite;
	std::weak_ptr<Actor> owner;
	std::shared_ptr<RenderComponent> RenderComp;
	std::vector<std::weak_ptr<CollisionComponent>> currentCollidors;

	bool enableDebug = false;
	

public:

	std::weak_ptr<Actor> GetOwner() 
	{
		return owner;
	};

	void SetCollisionState(bool State)
	{
		isColliding = State;
	};

	bool GetCollisionState()
	{
		return isColliding;
	};

	void UpdateCollidors(std::vector<std::weak_ptr<CollisionComponent>> CCS)
	{
		if (CCS.empty())
		{
			currentCollidors = {};
		}
		else
		{
			currentCollidors = CCS;
		}
		// This is not good practice learn a better way and change this....
		for (auto CC : CCS)
		{
			auto Collidor = CC.lock();

			if (!Collidor)
			{
				return;
			}

			if (!Collidor->isDamageCollidor)
			{
				SetCollisionState(true);
				return;
			}
		}

		SetCollisionState(false);
	}

	bool IsCurrentCollidor(std::weak_ptr<CollisionComponent> CC)
	{
		if (currentCollidors.empty() || !CC.lock())
		{
			return false;
		}
		else
		{
			auto iterator = std::find_if(currentCollidors.begin(), currentCollidors.end(),
				[CC] (const std::weak_ptr<CollisionComponent>& collidor)
				{
					return collidor.lock() == CC.lock();
				}

				);
			return (!currentCollidors.empty() && iterator != currentCollidors.end());
		}
	}
};

                                                             