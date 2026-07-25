#include "../Templates/Templates.h"
#include "Sprite.h"


// Animated Actors or tiles call this and animtor sets Image
Sprite::Sprite()
{
	spriteAnimator = SpawnActor<Animator>();
}

// Actors or Tiles with static Image need to call this 
Sprite::Sprite(const char* imagePath)
{
	spriteAnimator = SpawnActor<Animator>();
	DefaultImage = new Image(imagePath);
}
