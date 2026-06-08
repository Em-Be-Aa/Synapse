#pragma once

#include "../Sprite/Sprite.h"
#include "../Shader/Shader.h"
#include "../Camera/Camera.h"
#include <map>
#include "../Collision/CollisionComponent.h"
#include "../Shader/RenderComponent.h"
#include "../Enums&Structs/GameTypes.h"

class Character : public Actor
{

public:

	Character();
	void UpdateAnim(std::string Mode);
	void Tick(double deltaTime) override;

protected:

	Sprite characterSprite;
	std::string currentAnim = "IDLE";
	CollisionComponent Collidor;
	RenderComponent RenderComp;

	glm::vec3 characterFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 characterUp = glm::vec3(0.0f, 1.0f, 0.0f);

	std::map<std::string, Anim_Clip> animMontage = {};

	glm::vec3 previousPosition = glm::vec3(0.0f, 0.0f, 0.0003f);

	const char* defaultImage = "Assets/Player/Human/With_Shadows/Human_Soldier_Sword_Shield_Idle-Sheet.png";
};
