#include "Game/Game.h"

#define MA_IMPLEMENTATION
#include "Audio/miniaudio.h"

int main()
{
    // Fix this
    ma_result result;
    ma_engine engine;

    result = ma_engine_init(NULL, &engine);
    if (result != MA_SUCCESS) {
        return -1;
    }

    ma_engine_play_sound(&engine, "Assets/Audio/SoundTrack.mp3", NULL);


    Game* defaultGame = Game::GetGame();
    defaultGame->Init();

    return 0;
}


