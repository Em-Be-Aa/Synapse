#pragma once

#include "../Sprite/Sprite.h"
#include "../Shader/Shader.h"
#include "../Camera/Camera.h"
#include <map>

enum Anim_Mode 
{
	NONE,
	IDLE,
	WALK,
	JUMP,
};

struct Anim_Clip 
{
	Image* spriteSheet;
	glm::vec2 imageTiles;

	Anim_Clip() = default;
	Anim_Clip(const char* imagePath, glm::vec2 tileInfo) : spriteSheet(new Image(imagePath)), imageTiles(tileInfo) {}
};

class Character : public Actor
{

public:

	Character(const char* imagePath, Shader* defaultShader, Camera* Camera);
	void UpdateAnim(Anim_Mode Mode);
	virtual void Tick(double deltaTime) override;

	glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0003f);
	double Speed = 0.0f;
	glm::vec3 Velocity;

protected:

	Shader* characterShader;
	Camera* characterCamera;
	Sprite characterSprite;
	Image* currentSpritesheet = nullptr;
	Anim_Mode currentAnim = IDLE;

private:

	std::map<Anim_Mode, Anim_Clip> animMontage = {
	{ IDLE,   Anim_Clip("Assets/Player/Human/With_Shadows/Human_Soldier_Sword_Shield_Idle-Sheet.png",			{6, 1}) },
	{ WALK,   Anim_Clip("Assets/Player/Human/With_Shadows/Human_Soldier_Sword_Shield_Walk-Sheet.png",			{8, 1}) },
	{ JUMP,   Anim_Clip("Assets/Player/Human/With_Shadows/Human_Soldier_Sword_Shield_Jump_Fall-Sheet.png",		{6, 1}) },
	};

	glm::vec3 previousPosition = glm::vec3(0.0f, 0.0f, 0.0003f);
};
