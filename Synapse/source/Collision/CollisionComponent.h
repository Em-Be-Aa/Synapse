#pragma once

#include <glm/glm.hpp>
#include "../Actor/Object.h"
#include "../Shader/Shader.h"
#include "../Sprite/Sprite.h"
#include "../Enums&Structs/GameTypes.h"


class CollisionComponent : public Object
{

public:

	CollisionComponent(Shader* shader, const char* imagePath, Actor* ownerActor);
	void Tick(double deltaTime) override;

	CollisionBox Box;
	bool isColliding = false;
	glm::vec2 BoxSize = glm::vec2(1.0f, 1.0f);


private:

	Shader* collisionShader;
	Sprite collisionSprite;
	Actor* owner;
	
};

