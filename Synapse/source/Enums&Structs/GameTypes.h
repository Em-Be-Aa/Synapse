#pragma once

#include "../ImageLoader/Image.h"
#include <glm/glm.hpp>
#include <optional>
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
struct AbilityInfo {

	AbilityInfo() 
	{
		collidorSize   = {0, 0};
		collidorOffset = {0, 0};
		abilityDamage = 0;
		abilityCooldown = 0;
	}

	std::optional<glm::vec2> collidorSize;
	std::optional<glm::vec2> collidorOffset;
	float abilityDamage;
	float abilityCooldown;
	std::optional<float> dashDistance;
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
	TopCenter,
	BottomCenter,
	None
};

enum class Faction 
{
	Player,
	Enemy,
	None
};


struct Resource {
	float current;
	float max;
};

struct AbilityVital {

	std::string tag;
	float abilityDamage;
	float abilityCooldown;
	std::optional<float> dashDistance;
};

struct Vitals
{
	Resource Vigor; // Health
	float Momentum; // Speed
	Resource Plating; // Armor
	float Focus; // Crit Chance
	float Recovery; // Health Recovery
	int Insight; // Luck

	AbilityVital LightAttack;
	AbilityVital HeavyAttack;
	AbilityVital Dash;
};

struct CardInfo {

	std::string target = "HEAVY ATTACK";
	std::string id = "impact_damage_01";
	std::string title = "Crushing Blow";
	std::string description =  "Heavy Attack deals +15 damage.";
	std::string statTag =  "DAMAGE";
	float value =  15.0;
	bool isMultiplier = false;
	std::string icon = "Assets/UI/Cards/impact_dmg_icon.png";
	std::string vfxTag = "IMPACT_SHOCKWAVE";
};
