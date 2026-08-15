#pragma once

class Window;
class InputManager;
class Session;

class Game
{

public:

	void Init();
	void StartGame();
	void End();

	Window* GetGameWindow() { return gameWindow; };
	InputManager* GetInputManager() { return defaultInputManager; };

private:

	Window* gameWindow = nullptr;
	InputManager* defaultInputManager = nullptr;
	Session* gameSession = nullptr;

};

