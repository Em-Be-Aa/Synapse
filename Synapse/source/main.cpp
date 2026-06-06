#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader/Shader.h"
#include "Window/Window.h"
#include "Managers/InputManager.h"
#include "Camera/Camera.h"
#include "Managers/TickManager.h"
#include "Actor/Object.h"
#include "Tile/TileMap.h"
#include "Characters/Player.h"
#include "Characters/Enemy.h"
#include "Managers/CollisionManager.h"
#include "Managers/StatManager.h"

/* 
 
TODO:

1. Fix Collision Box moving for enemy when player moves. ✅
2. Make Renderer and remove logic from Tick.
3. Make Animation System include a single play of animation for attacks and stuff.
4. Make a Json system that loads info for the game at start and classes can use them(Player, Enemy, Tiles etc).
5. Make a grid system, all actors should be aware of their grid(or grid should have all actors in it). Through this make the collision system decoupled and moving actors should check for collision in their grid.
6. Movement along diagonal is faster, balance it.
7. Collidors of top and right stop player further from the other actors collision box.

*/


int main()
{
    Window DefaultWindow;

    // Managers
    InputManager DefaultInputManager(DefaultWindow.window);
    StatManager::Get();
    CollisionManager::GetCollisionManager();

    //make some system to manage all shaders and rendering.....adding it in actors logic is too hectic
    Shader FirstShader("Shaders/shader.vs", "Shaders/shader.fs");
    TileMap Landscape(&FirstShader); 

    // Actors
    Player SynapsePlayer(&FirstShader);
    Camera DefaultCamera(&SynapsePlayer);
    Enemy SlimeEnemy(&FirstShader);

    // Setting Input Actor
    DefaultInputManager.observers.push_back(&SynapsePlayer);
    DefaultInputManager.onMouseMove = ([&DefaultWindow, &DefaultCamera](double xpos, double ypos) { DefaultCamera.CameraMove(DefaultWindow.window, xpos, ypos); });
    
    
    //glEnable(GL_DEPTH_TEST);
    srand(time(0));

    double currentTime;
    double initialTime = glfwGetTime();
    double deltaTime = 0.0f;

    // Render Loop
    while (!glfwWindowShouldClose(DefaultWindow.window))
    {

        currentTime = glfwGetTime();
        deltaTime = currentTime - initialTime;
        initialTime = currentTime;


        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // 3D Transformation, Camera and Projection
        glm::mat4 model = glm::mat4(1.0f);

        glm::mat4 view;
        view = glm::lookAt(DefaultCamera.Position, DefaultCamera.Position + DefaultCamera.cameraFront, DefaultCamera.cameraUp);

        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), (DefaultWindow.Width / DefaultWindow.Height), 0.1f, 100.0f);

        int modelLoc = glGetUniformLocation(FirstShader.ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        int viewLoc = glGetUniformLocation(FirstShader.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        int projectionLoc = glGetUniformLocation(FirstShader.ID, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));


        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


        // Process Inputs
        DefaultInputManager.ProcessInputs();
        
        // Tick World
        for (Object* O : TickManager::GetTickManager()->RegisteredObjects)
        {
            O->Tick(deltaTime);
        }

        glfwSwapBuffers(DefaultWindow.window);
        glfwPollEvents();
    }


	// Cleanup and Exit
    glfwTerminate();
    return 0;
}


