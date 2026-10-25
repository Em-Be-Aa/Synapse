#pragma once
#include "Character.h"

class StateMachine;
class CharacterHealthBar;

class Enemy: public Character 
{

public:

	Enemy(glm::vec3 spawnPosition);

	void Init() override;
	void Tick(double deltaTime) override;

	void Destroy() override;

	std::shared_ptr<StateMachine> AIStateMachine;

private:

	std::shared_ptr<CharacterHealthBar> healthBar;
};

