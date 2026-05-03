#pragma once

#include "../Input/IInputObserver.h"

class Actor : public IInputObserver
{

public:

	Actor();

	unsigned int ID;

	virtual void Init();
	virtual void Tick(double deltaTime);

	virtual void onInputAction(int Key) override {};
};

