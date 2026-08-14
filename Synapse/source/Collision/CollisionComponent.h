#pragma once

#include "../Actor/Object.h"
#include "../Enums&Structs/GameTypes.h"
#include "../Shader/RenderComponent.h"
#include "../Shader/Shader.h"
#include "../Sprite/Sprite.h"
#include "../Templates/Templates.h"
#include <glm/glm.hpp>


class CollisionComponent : public Object
{

public:
	CollisionComponent(Actor* Owner);
	CollisionComponent(bool isDamage);
	CollisionComponent(Actor* Owner, bool isDamage);

	~CollisionComponent();

	// This is component of an actor...think about if this need tick or update....this goes for all components...the initial thought was to use update for managers, components so their logic runs before actors run tick
	void Update(double deltaTime) override;

	CollisionBox Box;
	bool isColliding = false;
	glm::vec2 BoxSize = glm::vec2(1.0f, 1.0f);
	bool isDamageCollidor = false;

	Delegate<CollisionInfo> CollisionDelegate;


private:

	Shader* collisionShader;
	Sprite collisionSprite;
	Actor* owner;
	RenderComponent RenderComp;

	std::vector<CollisionComponent*> currentCollidors;
	

public:

	Actor* GetOwner() 
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

	void UpdateCollidors(std::vector<CollisionComponent*> CCS)
	{
		
		if (CCS.empty())
		{
			currentCollidors = {};
		}
		else
		{
			currentCollidors = CCS;
		}

		for (auto CC : CCS)
		{
			if (!CC->isDamageCollidor)
			{
				SetCollisionState(true);
				return;
			}
		}

		SetCollisionState(false);
	}

	bool IsCurrentCollidor(CollisionComponent* CC)
	{
		if (currentCollidors.empty() || !CC)
		{
			return false;
		}
		else
		{
			auto iterator = std::find(currentCollidors.begin(), currentCollidors.end(), CC);
			return (!currentCollidors.empty() && iterator != currentCollidors.end());
		}
	}
};

                                                             