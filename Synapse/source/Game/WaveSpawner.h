#pragma once
#include "../Actor/Object.h"
#include "../Enums&Structs/GameTypes.h"
#include "../Templates/Templates.h"
#include <map>
#include <vector>

class Enemy;

class WaveSpawner : public Object
{
	
public:

	WaveSpawner(Session* session)
	{
		currentSession = session;
	}

	void Init() override;
	void StartWave(int CurrentWaveCount);
	void Update(double dT) override;

	Delegate<int> OnWaveCompleted;

	int GetCurrentEnemyCount() 
	{
		return currentEnemies.size();
	}

	int GetTotalEnemyCount()
	{
		return currentWaveInfo.enemyCount;
	}

	int GetCurrentWaveCount()
	{
		return currentWaveCount;
	}


private:

	glm::vec3 GetRandomSpawnPosition()
	{
		int columns = 30;
		int rows = 30;
		float tileSize = 1.0f;

		// Generate a random X and Y grid index from -15 to +14 (just like your tilemap)
		int randomX = (rand() % columns) - (columns / 2);
		int randomY = (rand() % rows) - (rows / 2);

		// Convert to world space coordinates and add your specific Z depth
		float worldX = (float)randomX * tileSize;
		float worldY = -(float)randomY * tileSize; // Negative Y just like your TileMap logic

		return glm::vec3(worldX, worldY, 0.0003f);
	}

	std::map<int, WaveInfo> Wave = {
	{ 1, {1} },
	{ 2, {2} },
	{ 3, {3} },
	{ 4, {6} },
	{ 5, {8} },
	{ 6, {12} }
	};

	std::vector<Enemy*> currentEnemies;
	Session* currentSession;
	int currentWaveCount;
	WaveInfo currentWaveInfo;

	bool isWaveEnded = true;


};

