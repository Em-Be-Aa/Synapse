#pragma once

#include "../Interfaces/IInputObserver.h"
#include "Object.h"
#include <glm/glm.hpp>

class Actor : public Object, public IInputObserver
{

public:

	Actor();

	virtual void Init();
	void onInputAction(int Key) override {};

	unsigned int ID;
	glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0003f);

};

