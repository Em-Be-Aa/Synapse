#include "../AI/StateMachine/StateMachine.h"
#include "../Characters/Enemy.h"
#include "../Characters/Player.h"
#include "../Game/Session.h"
#include "WaveSpawner.h"
#include <iostream>

void WaveSpawner::StartWave(int CurrentWaveCount)
{
    std::cout << "Starting Wave Number :" << CurrentWaveCount << std::endl;

    auto it = Wave.find(CurrentWaveCount);

    WaveInfo currentWave;

    if (it != Wave.end())
    {
        currentWave = it->second;

        Player* currentPlayer = currentSession->GetActivePlayer();
        currentEnemies.clear();

        currentWaveCount = CurrentWaveCount;

        for (size_t i = 0; i < currentWave.enemyCount; i++)
        {

            Enemy* newEnemy = SpawnActor<Enemy>(GetRandomSpawnPosition());
            newEnemy->GetAbilityComponent().AddAbility("LIGHT ATTACK");
            newEnemy->AIStateMachine = SpawnActor<StateMachine>(newEnemy, currentPlayer);
            currentEnemies.push_back(newEnemy);
        }

    }
    else
    {
        std::cout << "Wave Number was not found in the map" << std::endl;
        return;
    }
}

void WaveSpawner::Update(double dT)
{
    for (int i = currentEnemies.size() - 1; i >= 0; i--)
    {
        // This is not right and should crash but doesn't so well fix it when the time comes
        if (currentEnemies[i]->isPendingDestroy)
        {
            currentEnemies.erase(currentEnemies.begin() + i);
        }
    }

    if (currentEnemies.empty())
    {
        currentWaveCount++;
        StartWave(currentWaveCount);
    }
}
