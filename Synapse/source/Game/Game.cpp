#include "../GameConfig/GameConfigs.h"
#include "../Managers/InputManager.h"
#include "../Shader/Renderer2D.h"
#include "../Window/Window.h"
#include "Game.h"
#include "Session.h"
#include <GLFW/glfw3.h>

void Game::Init()
{

    gameWindow = new Window();
    gameWindow->SetInputModeGame();
    defaultInputManager = new InputManager(gameWindow->window);
    Renderer2D::GetRenderer()->Init("Shaders/shader.vs", "Shaders/shader.fs");
    GameConfigs::GetGameConfig();

    StartGame();


    double currentTime;
    double initialTime = glfwGetTime();
    double deltaTime = 0.0f;   
    


    while (!glfwWindowShouldClose(gameWindow->window))
    {

        currentTime = glfwGetTime();
        deltaTime = currentTime - initialTime;
        initialTime = currentTime;

        gameSession->Update(deltaTime);
    }

}

void Game::StartGame()
{
    if (gameSession)
    {
        delete gameSession;
    }
    
    gameSession = new Session(this);
    gameSession->Init();

}

void Game::End()
{
    Renderer2D::GetRenderer()->Shutdown();
    glfwTerminate();
}

