#pragma once

#include "../ImageLoader/Image.h"
#include <glm/glm.hpp>
#include <string>

class Actor;

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
	bool isMontage = false;

	Anim_Clip() = default;
	Anim_Clip(const char* imagePath, glm::vec2 tileInfo, bool state) : spriteSheet(new Image(imagePath)), imageTiles(tileInfo), isMontage(state) {}
};

struct CollisionBox
{
	glm::vec2 min;
	glm::vec2 max;
};

enum TileType {
	None,
	Grass,
	Land,
	Water
};

struct AnimationClip {
	std::string imagepath;
	int tileX = 1;
	int tileY = 1;
};

struct KeyState {
	bool wasPressed = false;
	bool isPressed = false;
};

struct CollisionInfo {
	Actor* Collidor;
	bool isDamageCollidor = false;
	float damageCount = 0;
	std::vector<Actor*> ignoreActors;
};

// This should also inlcude the time offsets start and end
struct AbilityCollisionInfo {

	AbilityCollisionInfo() 
	{
		collidorSize   = {0, 0};
		collidorOffset = {0, 0};
		collidorDamage = 0;
	}

	glm::vec2 collidorSize;
	glm::vec2 collidorOffset;
	float collidorDamage;
};

struct WaveInfo
{
	int enemyCount = 0;
};

enum RenderSpace
{
	World, 
	Screen
};


struct Submission 
{
	unsigned int textureID; 
	glm::mat4 model; 
	glm::vec4 uv; 
	glm::vec4 tint; 
	int layer; 
	bool textureXFlip; 
	RenderSpace space;
};

enum class AnchorPoint {
	TopLeft,
	BottomLeft,
	TopRight,
	BottomRight,
	Center,
	None
};

enum class Faction 
{
	Player,
	Enemy,
	None
};