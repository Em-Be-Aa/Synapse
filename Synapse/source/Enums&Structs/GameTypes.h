#pragma once

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