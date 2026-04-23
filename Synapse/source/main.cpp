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


float deltaTime = 0.0f;	
float lastFrame = 0.0f;


int main()
{
    // Window
    Window DefaultWindow;

    // Input Manger
    InputManager InputManager(DefaultWindow.window);

    // Camera
    Camera DefaultCamera;

    // Shaders
    Shader FirstShader("Shaders/shader.vs", "Shaders/shader.fs");

    TileManager tileMap(&FirstShader); 

    Player SynapsePlayer("Assets/Player/Alchemist/PNG/PNG Sequences/Idle Blinking/0_Bloody_Alchemist_Idle Blinking_000.png", &FirstShader);



    // Bind Inputs 
    //InputManager.BindKey(GLFW_KEY_ESCAPE, [&DefaultWindow]() { glfwSetWindowShouldClose(DefaultWindow.window, true); });
    //InputManager.BindKey(GLFW_KEY_Q, [&DefaultCamera]() { DefaultCamera.cameraPosition += DefaultCamera.cameraSpeed * DefaultCamera.cameraFront; });
    //InputManager.BindKey(GLFW_KEY_E, [&DefaultCamera]() { DefaultCamera.cameraPosition -= DefaultCamera.cameraSpeed * DefaultCamera.cameraFront; });
    //InputManager.BindKey(GLFW_KEY_A, [&DefaultCamera]() { DefaultCamera.cameraPosition -= glm::normalize(glm::cross(DefaultCamera.cameraFront, DefaultCamera.cameraUp)) * DefaultCamera.cameraSpeed; });
    //InputManager.BindKey(GLFW_KEY_D, [&DefaultCamera]() { DefaultCamera.cameraPosition += glm::normalize(glm::cross(DefaultCamera.cameraFront, DefaultCamera.cameraUp)) * DefaultCamera.cameraSpeed; });
    //InputManager.BindKey(GLFW_KEY_W, [&DefaultCamera]() { DefaultCamera.cameraPosition[1] = DefaultCamera.cameraPosition[1] + DefaultCamera.cameraSpeed; });
    //InputManager.BindKey(GLFW_KEY_S, [&DefaultCamera]() { DefaultCamera.cameraPosition[1] = DefaultCamera.cameraPosition[1] - DefaultCamera.cameraSpeed; });
    //InputManager.onMouseMove = ([&DefaultWindow, &DefaultCamera](double xpos, double ypos) { DefaultCamera.CameraMove(DefaultWindow.window, xpos, ypos); });


    InputManager.BindKey(GLFW_KEY_ESCAPE, [&DefaultWindow]() { glfwSetWindowShouldClose(DefaultWindow.window, true); });
    //InputManager.BindKey(GLFW_KEY_Q, [&DefaultCamera]() { DefaultCamera.cameraPosition += DefaultCamera.cameraSpeed * DefaultCamera.cameraFront; });
    //InputManager.BindKey(GLFW_KEY_E, [&DefaultCamera]() { DefaultCamera.cameraPosition -= DefaultCamera.cameraSpeed * DefaultCamera.cameraFront; });
    InputManager.BindKey(GLFW_KEY_A, [&DefaultCamera]() { DefaultCamera.cameraPosition -= glm::normalize(glm::cross(DefaultCamera.cameraFront, DefaultCamera.cameraUp)) * DefaultCamera.cameraSpeed; });
    InputManager.BindKey(GLFW_KEY_D, [&DefaultCamera]() { DefaultCamera.cameraPosition += glm::normalize(glm::cross(DefaultCamera.cameraFront, DefaultCamera.cameraUp)) * DefaultCamera.cameraSpeed; });
    InputManager.BindKey(GLFW_KEY_W, [&DefaultCamera]() { DefaultCamera.cameraPosition[1] = DefaultCamera.cameraPosition[1] + DefaultCamera.cameraSpeed; });
    InputManager.BindKey(GLFW_KEY_S, [&DefaultCamera]() { DefaultCamera.cameraPosition[1] = DefaultCamera.cameraPosition[1] - DefaultCamera.cameraSpeed; });
    InputManager.onMouseMove = ([&DefaultWindow, &DefaultCamera](double xpos, double ypos) { DefaultCamera.CameraMove(DefaultWindow.window, xpos, ypos); });
    
    
    glEnable(GL_DEPTH_TEST);

    double previousTime = glfwGetTime();
    int frameCount = 0;

    srand(time(0));


    // Render Loop
    while (!glfwWindowShouldClose(DefaultWindow.window))
    {

        double currentTime = glfwGetTime();

        // 2. We rendered a frame, so count it!
        frameCount++;

        // 3. Has a full second passed since we last printed?
        if (currentTime - previousTime >= 1.0)
        {
            // Print the FPS
            std::cout << "FPS: " << frameCount << std::endl;

            // Reset for the next second
            frameCount = 0;
            previousTime = currentTime;
        }


        // Delta Time
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        DefaultCamera.cameraSpeed = 2.5 * deltaTime;
        std::cout << "Camera Position is as follows: " << DefaultCamera.cameraPosition.x << std::endl;
        SynapsePlayer.playerPosition = {DefaultCamera.cameraPosition.x, DefaultCamera.cameraPosition.y , 0.0003};

        // Input Processing
        InputManager.ProcessInputs();


        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //FirstShader.use();

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


