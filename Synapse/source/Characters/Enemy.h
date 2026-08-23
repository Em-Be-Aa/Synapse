#pragma once
#include "Character.h"

class StateMachine;
class CharacterHealthBar;

class Enemy: public Character 
{

public:

	Enemy(glm::vec3 spawnPosition);

	void Tick(double deltaTime) override;

	void Destroy() override;

	StateMachine* AIStateMachine;

private:

	CharacterHealthBar* healthBar;
};

