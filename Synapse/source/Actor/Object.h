#pragma once

#include "../Interfaces/IUpdate.h"
#include <memory>


class Object : public IUpdate, public std::enable_shared_from_this<Object>
{
public: 

	Object();
	virtual ~Object();

	virtual void Update(double deltaTime) = 0;
	virtual void Init() {};
	virtual void Destroy() 
	{
		isPendingDestroy = true;
	};

	bool isPendingDestroy = false;
};

                