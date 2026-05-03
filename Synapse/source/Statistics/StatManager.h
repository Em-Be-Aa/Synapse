#pragma once

#include "../Actor/Actor.h"


class StatManager : public Actor
{

public:

	static StatManager& Get() 
	{
		static StatManager instance;
		return instance;
	};

	double initialTime = 0.0f;
	double currentTime = 0.0f;
	int frameCount = 0;
	int drawCalls = 0;

	bool enableDrawcalls = true;
	bool enableFPS = true;

	void Tick(double deltaTime) override;

private:
	StatManager();
};

