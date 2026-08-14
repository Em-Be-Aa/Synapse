#pragma once

#include "../Interfaces/IInputObserver.h"
#include "../Interfaces/ITicker.h"
#include "Object.h"
#include <glm/glm.hpp>


// Classes should not be actor if they just want tick...they can use the interface themselves...
class Actor : public Object, public IInputObserver, public ITicker
{

public:

	Actor();
	~Actor();

	void Init() override;
	void Destroy() override;
	void Tick(double deltaTime) override {};
	void Update(double deltaTime) override {};
	void onInputPressed(int Key) override {};
	void onInputReleased(int Key) override {};
	void onInputClicked(int Key) override {};

	unsigned int ID;
	glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0003f);

	void SetDeltaPosition(glm::vec3 dP)
	{
		deltaPosition = dP;
	}


protected:

	double Speed = 0.0f;
	glm::vec3 Velocity;
	float movementSpeed = 1.0f;
	glm::vec3 deltaPosition;

};

