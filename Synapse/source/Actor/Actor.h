#pragma once

#include "../Input/IInputObserver.h"
#include <glm/glm.hpp>

class Actor : public IInputObserver
{

public:

	Actor();

	virtual void Init();
	virtual void Tick(double deltaTime);
	virtual void onInputAction(int Key) override {};

	unsigned int ID;
	glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0003f);


protected:

};

