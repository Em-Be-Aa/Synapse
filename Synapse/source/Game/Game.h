#pragma once

class Window;
class InputManager;
class Session;

class Game
{

public:

	static Game& GetGame()
	{
		static Game game;
		return game;
	};

	void Init();
	void StartGame();
	void End();

	Window* GetGameWindow() { return gameWindow; };
	InputManager* GetInputManager() { return defaultInputManager; };

	Session* GetCurrentSession()
	{
		return gameSession;
	}

private:

	Game() {};

	Window* gameWindow = nullptr;
	InputManager* defaultInputManager = nullptr;
	Session* gameSession = nullptr;

};

