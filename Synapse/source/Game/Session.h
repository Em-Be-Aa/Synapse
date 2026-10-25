#pragma once
#include "../UI/Base/HUD.h"
#include "Game.h"

class TileMap;
class Player;
class Enemy;
class Camera;
class WaveSpawner;

class Session : public std::enable_shared_from_this<Session>
{

public:

	Session(Game* Game)
	{
		game = Game;
	}

	void Init();
	void Update(double deltaTime);

	std::weak_ptr<Player> GetActivePlayer()
	{
		return SynapsePlayer;
	};

	std::weak_ptr<Font> GetLargeFont() 
	{
		return largeFont;
	}

	std::weak_ptr<Font> GetDefaultFont()
	{
		return defaultFont;
	}

	std::weak_ptr<Font> GetSmallFont()
	{
		return smallFont;
	}

	std::weak_ptr<WaveSpawner> GetWaveSpawner()
	{
		return waveSpawner;
	}

private:


	std::shared_ptr<TileMap> Landscape ;
	std::shared_ptr<Player> SynapsePlayer;
	std::shared_ptr<Camera> defaultCamera;
	std::shared_ptr<HUD> sessionHUD;
	std::shared_ptr<WaveSpawner> waveSpawner;
	std::shared_ptr<Font> largeFont;
	std::shared_ptr<Font> defaultFont;
	std::shared_ptr<Font> smallFont;
	Game* game;

};

