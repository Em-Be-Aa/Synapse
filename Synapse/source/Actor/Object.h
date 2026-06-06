#pragma once

#include "../Interfaces/ITicker.h"


class Object : public ITicker
{
public: 

	Object();

	virtual void Tick(double deltaTime) override {};

};

