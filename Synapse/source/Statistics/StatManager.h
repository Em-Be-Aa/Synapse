#pragma once

#include "../Actor/Actor.h"


class StatManager : public Actor
{

public:

	double initialTime = 0.0f;
	double currentTime = 0.0f;
	int frameCount = 0;

	StatManager();
	void Tick() override;

};

