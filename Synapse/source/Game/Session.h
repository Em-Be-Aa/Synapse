#pragma once
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


private:


	TileMap* Landscape ;
	Player* SynapsePlayer;
	Camera* defaultCamera;
	WaveSpawner* waveSpawner;

	Game* game;

};

