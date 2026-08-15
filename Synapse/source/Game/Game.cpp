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
    defaultInputManager = new InputManager(gameWindow->window);
    Renderer2D::Init("Shaders/shader.vs", "Shaders/shader.fs");
    GameConfigs::GetGameConfig();

    StartGame();

}

void Game::StartGame()
{
    if (!gameSession)
    {
        delete gameSession;
    }
    
    gameSession = new Session(this);
    gameSession->Init();

}

void Game::End()
{
    Renderer2D::Shutdown();
    glfwTerminate();
}

