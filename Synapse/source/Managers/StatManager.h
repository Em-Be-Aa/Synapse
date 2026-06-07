#pragma once

#include "../Actor/Actor.h"


class StatManager : public Object
{

public:

	void Tick(double deltaTime) override;
	static StatManager& Get() 
	{
		static StatManager instance;
		return instance;
	};

	int drawCalls = 0;

private:

	StatManager();

	double initialTime = 0.0f;
	double currentTime = 0.0f;
	int frameCount = 0;
	bool enableStats = false;
};

