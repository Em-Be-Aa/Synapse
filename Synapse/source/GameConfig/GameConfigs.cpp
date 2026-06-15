#include "../Managers/SynapseFunctionLibrary.h"
#include "GameConfigs.h"


GameConfigs::GameConfigs()
{
    Config = SynapseFunctionLibrary::loadJson();
}

GameConfigs& GameConfigs::GetGameConfig()
{
    static GameConfigs Config;
    return Config;
}

// Loads Character Animations
std::map<std::string, Anim_Clip> GameConfigs::GetCharacterData(std::string characterName)
{
    std::map<std::string, Anim_Clip> characterData;

    if (Config != nullptr)
    {
        auto& animations = Config[characterName]["animations"];
        for (auto& [animName, animData] : animations.items())
        {
            std::string path = animData["path"].get<std::string>();
            int frames = animData["frames"].get<int>();
            bool isMontage = animData["isMontage"].get<bool>();
            characterData.insert({ animName, Anim_Clip(path.c_str(), {frames, 1}, isMontage)});
        }

        return characterData;
    }
}
