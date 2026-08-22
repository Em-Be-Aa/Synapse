#include "Game/Game.h"

int main()
{
    Game* defaultGame = Game::GetGame();
    defaultGame->Init();

    return 0;
}


