#pragma once
class Actor
{

public:

	Actor();

	unsigned int ID;

	virtual void Init();

	virtual void Tick();
};

