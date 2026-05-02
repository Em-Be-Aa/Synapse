#pragma once

#include <GLFW/glfw3.h>
#include <map>
#include <functional>
#include "../Actor/Actor.h"
#include "IInputObserver.h"



class InputManager
{
public:

	InputManager(GLFWwindow* window);
    void ProcessInputs();
    static void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);

    std::function<void(double, double)> onMouseMove;
	GLFWwindow* InputWindow;

    std::vector<IInputObserver*> observers = {};

private:

    std::vector<int> inputActions = 
    { 
        // --- Movement / Main Letters ---
        GLFW_KEY_W,
        GLFW_KEY_A,
        GLFW_KEY_S,
        GLFW_KEY_D,
        GLFW_KEY_Q,
        GLFW_KEY_E,

        // --- Actions & Modifiers ---
        GLFW_KEY_SPACE,        
        GLFW_KEY_ESCAPE,      
        GLFW_KEY_ENTER,
        GLFW_KEY_LEFT_SHIFT,   
        GLFW_KEY_LEFT_CONTROL, 
        GLFW_KEY_TAB,        

        // --- Arrows ---
        GLFW_KEY_UP,   
        GLFW_KEY_DOWN,  
        GLFW_KEY_LEFT, 
        GLFW_KEY_RIGHT,

    };

};
