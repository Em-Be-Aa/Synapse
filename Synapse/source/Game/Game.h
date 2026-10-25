#pragma once

#include <memory>

class Window;
class InputManager;
class Session;

class Game
{

public:

	void Init();
	void StartGame();
	void End();


private:

	Game() {};

	std::shared_ptr<InputManager> defaultInputManager = nullptr;
	std::shared_ptr<Session> gameSession = nullptr;
	std::shared_ptr<Window> gameWindow = nullptr;


public:

 	static Game* GetGame()
	{
		static Game game;
		return &game;
	};

	std::weak_ptr<Window> GetGameWindow() { return gameWindow; };
	std::weak_ptr<InputManager> GetInputManager() { return defaultInputManager; };
	std::weak_ptr<Session> GetCurrentSession() { return gameSession; }

};

