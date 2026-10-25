#include "../GameConfig/GameConfigs.h"
#include "../Managers/InputManager.h"
#include "../Shader/Renderer2D.h"
#include "../Window/Window.h"
#include "Game.h"
#include "Session.h"
#include <GLFW/glfw3.h>

void Game::Init()
{

    gameWindow = std::make_shared<Window>();
    gameWindow->SetInputModeGame();
    defaultInputManager = std::make_shared<InputManager>(gameWindow);
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


// Test by making some main menu shit....the session should be started again with nothing from previous session being stale or dangling or alive....the session and everything in it should completely start from scratch
void Game::StartGame()
{
    if (gameSession)
    {
        gameSession.reset();
    }
    
    gameSession = std::make_shared<Session>(this);
    gameSession->Init();

}

void Game::End()
{
    // make clean removal..even if this dont crash and game exits...
    Renderer2D::GetRenderer()->Shutdown();
    glfwTerminate();
}

