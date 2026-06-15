#pragma once

class ITicker
{
public:
	virtual void Tick(double deltaTime) = 0;

	bool enableTick = true;
};

