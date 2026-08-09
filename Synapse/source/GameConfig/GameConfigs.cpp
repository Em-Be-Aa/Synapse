#include "../Managers/SynapseFunctionLibrary.h"
#include "GameConfigs.h"
#include <iostream>


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

// Loads Character Abilities...check if ref is necessary and what wrong are we doing using simple struct...is copy bad here
AbilityCollisionInfo GameConfigs::GetCharacterAbilityData(std::string abilityName)
{
    AbilityCollisionInfo characterAbility;

    if (Config != nullptr)
    {
        auto& ability = Config["player"]["abilities"][abilityName];

        if (!ability.is_null())
        {
            glm::vec2 collidorSize = { ability["collidorSize"]["x"].get<float>(), ability["collidorSize"]["y"].get<float>()};
            glm::vec2 collidorOffset = { ability["collidorOffset"]["x"].get<float>(), ability["collidorOffset"]["y"].get<float>() };
            characterAbility.collidorSize = collidorSize;
            characterAbility.collidorOffset = collidorOffset;
        }
        else
        {
            std::cout << "Error: Could not find ability collision info" << std::endl;
        }

        return characterAbility;
    }
    else
    {
        //make a better logging system....warining, display and error..with colors...hahaha
        std::cout << "Config is null" << std::endl;
    }
}
