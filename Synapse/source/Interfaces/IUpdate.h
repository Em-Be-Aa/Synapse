#pragma once

// This is for objects to update things each frame. Runs before Tick so actors can use the updated info when update is completed.
class IUpdate
{
public:
	virtual void Update(double deltaTime) = 0;

	bool enableUpdate = true;
};

