#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader/Shader.h"
#include "ImageLoader/Image.h"
#include "Window/Window.h"
#include "Input/InputManager.h"
#include "Camera/Camera.h"
#include "Actor/ActorManager.h"
#include "Tile/TileManager.h"
#include "Player/Player.h"
#include "Statistics/StatManager.h"


int main()
{
    Window DefaultWindow;
    InputManager DefaultInputManager(DefaultWindow.window);
    Camera DefaultCamera;
    Shader FirstShader("Shaders/shader.vs", "Shaders/shader.fs");
    StatManager StatLogger;
    TileManager tileMap(&FirstShader); 
    Player SynapsePlayer("Assets/Player/Alchemist/PNG/PNG Sequences/Idle Blinking/0_Bloody_Alchemist_Idle Blinking_000.png", &FirstShader, &DefaultCamera);

    DefaultInputManager.observers.push_back(&DefaultCamera);
    DefaultInputManager.onMouseMove = ([&DefaultWindow, &DefaultCamera](double xpos, double ypos) { DefaultCamera.CameraMove(DefaultWindow.window, xpos, ypos); });
    
    
    glEnable(GL_DEPTH_TEST);
    srand(time(0));


    // Render Loop
    while (!glfwWindowShouldClose(DefaultWindow.window))
    {

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // 3D Transformation, Camera and Projection
        glm::mat4 model = glm::mat4(1.0f);

        glm::mat4 view;
        view = glm::lookAt(DefaultCamera.cameraPosition, DefaultCamera.cameraPosition + DefaultCamera.cameraFront, DefaultCamera.cameraUp);

        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        
        int modelLoc = glGetUniformLocation(FirstShader.ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        int viewLoc = glGetUniformLocation(FirstShader.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        int projectionLoc = glGetUniformLocation(FirstShader.ID, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


        // Input Processing
        DefaultInputManager.ProcessInputs();
        
        for (Actor* actor : ActorManager::GetActorManager()->RegisteredActors)
        {
            actor->Tick();
        }


        glfwSwapBuffers(DefaultWindow.window);
        glfwPollEvents();
    }


	// Cleanup and Exit
    glfwTerminate();
    return 0;
}


