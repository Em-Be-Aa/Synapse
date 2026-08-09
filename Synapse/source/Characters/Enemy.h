#pragma once

#include "Character.h"

class Enemy: public Character 
{

public:

	Enemy();

	void Tick(double deltaTime) override;
};

