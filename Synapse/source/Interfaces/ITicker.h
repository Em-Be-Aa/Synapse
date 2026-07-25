#pragma once


// Tick for Actors in the world. Runs after all frame functions are complete(ProcessInputs, Update etc)
class ITicker
{
public:
	virtual void Tick(double deltaTime) = 0;

	bool enableTick = true;
};

