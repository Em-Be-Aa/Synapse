#pragma once

#include "../Actor/Actor.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Camera: public Actor
{

public:

	Camera(Actor* AttachedActor);

	glm::vec3 cameraFront	= glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp		= glm::vec3(0.0f, 1.0f, 0.0f);

	bool firstMouse = true;

	float lastX = 800.0f / 2.0; // resolution should not be hardcoded here
	float lastY = 600.0 / 2.0;

	float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	float pitch = 0.0f;

	bool enable3D = false;

	Actor* attachedActor = nullptr;

	void CameraMove(GLFWwindow* window, double xposIn, double yposIn);


	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	void Update(double deltaTime) override;

};

