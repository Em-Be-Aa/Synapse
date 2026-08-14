#pragma once

#include "../Actor/Actor.h"
#include "../Enums&Structs/GameTypes.h"
#include <functional>
#include <GLFW/glfw3.h>
#include <map>



class InputManager
{

public:

	InputManager(GLFWwindow* window);
	void ProcessInputs();
	static void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);

	std::function<void(double, double)> onMouseMove;
	GLFWwindow* InputWindow;

	void EnableActorInput(Actor* actor)
	{
		observers.push_back(actor);
	}

	void DisableInputforPendingDestoryed()
	{
		std::erase_if(observers, [](const Actor* actor) { return actor->isPendingDestroy; });
	}

private:

	// I dont think struct is needed as a simple wasdown bool is enough
	std::map<int, KeyState> inputActions =
	{
		// --- Movement / Main Letters ---
        {GLFW_KEY_W, { false, false}},
	    {GLFW_KEY_A, { false, false}},
	    {GLFW_KEY_S, { false, false}},
	    {GLFW_KEY_D, { false, false}},
	    {GLFW_KEY_Q, { false, false}},
	    {GLFW_KEY_E, { false, false}},

		// --- Actions & Modifiers ---
		{GLFW_KEY_SPACE,{ false, false} },
		{GLFW_KEY_ESCAPE, { false, false }},
		{GLFW_KEY_ENTER, { false, false }},
		{GLFW_KEY_LEFT_SHIFT, { false, false }},
		{GLFW_KEY_LEFT_CONTROL, { false, false }},
		{GLFW_KEY_TAB, { false, false }},

		// --- Arrows ---
		{GLFW_KEY_UP, { false, false }},
		{GLFW_KEY_DOWN, { false, false }},
		{GLFW_KEY_LEFT, { false, false }},
		{GLFW_KEY_RIGHT, { false, false }},

		// --- Abilities ---
		{GLFW_KEY_Q, { false, false }},
		{GLFW_KEY_E, { false, false }},
		{GLFW_KEY_G, { false, false }},

		// --- Mouse Buttons ---
		{GLFW_MOUSE_BUTTON_1, { false, false }},
		{GLFW_MOUSE_BUTTON_2, { false, false }}
	};

	std::vector<Actor*> observers = {};
};
