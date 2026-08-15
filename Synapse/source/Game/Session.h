#pragma once
#include "Game.h"


class Session
{

public:

	Session(Game* Game)
	{
		game = Game;
	}

	void Init();


private:

	Game* game;

};

