#include "../AI/StateMachine/StateMachine.h"
#include "../Characters/Abilities/AttackAbility.h"
#include "../Characters/Enemy.h"
#include "../Characters/Player.h"
#include "../Game/Session.h"
#include "../GameConfig/GameConfigs.h"
#include "WaveSpawner.h"
#include <iostream>

void WaveSpawner::Init()
{

}

void WaveSpawner::StartWave(int CurrentWaveCount)
{
    std::cout << "Starting Wave Number :" << CurrentWaveCount << std::endl;
    isWaveEnded = false;

    auto it = Wave.find(CurrentWaveCount);

    WaveInfo currentWave;

    if (it != Wave.end())
    {
        currentWaveInfo = it->second;

        Player* currentPlayer = currentSession->GetActivePlayer();
        currentEnemies.clear();

        currentWaveCount = CurrentWaveCount;

        for (size_t i = 0; i < currentWaveInfo.enemyCount; i++)
        {

            Enemy* newEnemy = SpawnActor<Enemy>(GetRandomSpawnPosition());
            AbilityInfo LightAttack = GameConfigs::GetGameConfig().GetCharacterAbilityData(newEnemy->GetCharacterTag(), "LIGHT ATTACK");
            AddAbility<AttackAbility>(newEnemy, "LIGHT ATTACK", LightAttack);
            newEnemy->GetVitalsComponent().SetVitals({ {100.0f, 100.0f }, 1.0f, {0.0f, 0.0f}, 0.0f, 0.0f, 0, {"LIGHT ATTACK", LightAttack.abilityDamage, LightAttack.abilityCooldown}, {"HEAVY ATTACK", 0.0f, 0.0f}, {"DASH", 0.0f, 0.0f}});
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

    if (!isWaveEnded && currentEnemies.empty())
    {
        isWaveEnded = true;
        currentWaveCount++;
        OnWaveCompleted.Broadcast(currentWaveCount);
    }
}
