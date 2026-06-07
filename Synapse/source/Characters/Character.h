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
	void UpdateAnim(Anim_Mode Mode);
	void Tick(double deltaTime) override;

protected:

	Sprite characterSprite;
	Anim_Mode currentAnim = IDLE;
	CollisionComponent Collidor;
	RenderComponent RenderComp;

	glm::vec3 characterFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 characterUp = glm::vec3(0.0f, 1.0f, 0.0f);

	std::map<Anim_Mode, Anim_Clip> animMontage = {
	{ IDLE,   Anim_Clip("Assets/Player/Human/With_Shadows/Human_Soldier_Sword_Shield_Idle-Sheet.png",			{6, 1}) },
	{ WALK,   Anim_Clip("Assets/Player/Human/With_Shadows/Human_Soldier_Sword_Shield_Walk-Sheet.png",			{8, 1}) },
	{ JUMP,   Anim_Clip("Assets/Player/Human/With_Shadows/Human_Soldier_Sword_Shield_Jump_Fall-Sheet.png",		{6, 1}) },
	};

	glm::vec3 previousPosition = glm::vec3(0.0f, 0.0f, 0.0003f);

	const char* defaultImage = "Assets/Player/Human/With_Shadows/Human_Soldier_Sword_Shield_Idle-Sheet.png";
};
