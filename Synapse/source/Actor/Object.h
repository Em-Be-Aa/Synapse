#pragma once

#include "../Interfaces/IUpdate.h"


class Object : public IUpdate
{
public: 

	Object();
	virtual ~Object();

	virtual void Update(double deltaTime) = 0;
	virtual void Init() {};
	virtual void Destroy() {};

	bool isPendingDestroy = false;
};

