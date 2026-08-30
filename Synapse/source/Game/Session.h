#pragma once
#include "../UI/Base/HUD.h"
#include "Game.h"

class TileMap;
class Player;
class Enemy;
class Camera;
class WaveSpawner;

class Session
{

public:

	Session(Game* Game)
	{
		game = Game;
	}

	void Init();
	void Update(double deltaTime);

	Player* GetActivePlayer()
	{
		return SynapsePlayer;
	};

	Font* GetLargeFont() 
	{
		return &largeFont;
	}

	Font* GetDefaultFont()
	{
		return &defaultFont;
	}

	Font* GetSmallFont()
	{
		return &smallFont;
	}

	WaveSpawner* GetWaveSpawner()
	{
		return waveSpawner;
	}

private:


	TileMap* Landscape ;
	Player* SynapsePlayer;
	Camera* defaultCamera;
	HUD* sessionHUD;
	WaveSpawner* waveSpawner;
	Font largeFont;
	Font defaultFont;
	Font smallFont;

	Game* game;

};

