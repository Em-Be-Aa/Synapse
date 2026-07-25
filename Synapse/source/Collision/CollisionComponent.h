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

	CollisionComponent();
	// This is component of an actor...think about if this need tick or update....this goes for all components...the initial thought was to use update for managers, components so their logic runs before actors run tick
	void Update(double deltaTime) override;

	CollisionBox Box;
	bool isColliding = false;
	glm::vec2 BoxSize = glm::vec2(1.0f, 1.0f);

	Delegate<CollisionInfo, void> CollisionDelegate;


private:

	Shader* collisionShader;
	Sprite collisionSprite;
	Actor* owner;
	RenderComponent RenderComp;
	

public:

	Actor* GetOwner() 
	{
		return owner;
	};

	void SetCollisionState(bool State)
	{
		isColliding = State;
	};

};

                                                             