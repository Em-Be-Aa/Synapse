#include "../Managers/SynapseFunctionLibrary.h"
#include "GameConfigs.h"
#include <iostream>
#include <random>


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
AbilityCollisionInfo GameConfigs::GetCharacterAbilityData(std::string characterTag, std::string abilityName)
{
    AbilityCollisionInfo characterAbility;

    if (Config != nullptr)
    {
        auto& ability = Config[characterTag]["abilities"][abilityName];

        if (!ability.is_null())
        {
            glm::vec2 collidorSize = { ability["collidorSize"]["x"].get<float>(), ability["collidorSize"]["y"].get<float>()};
            glm::vec2 collidorOffset = { ability["collidorOffset"]["x"].get<float>(), ability["collidorOffset"]["y"].get<float>() };
            float collidorDamage = ability["collidorDamage"].get<float>();
            characterAbility.collidorSize = collidorSize;
            characterAbility.collidorOffset = collidorOffset;
            characterAbility.collidorDamage = collidorDamage;
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

std::vector<CardInfo> GameConfigs::GetCardsData(std::vector<std::string> categories)
{
    std::vector<CardInfo> cardsInfo;

    if (Config == nullptr)
    {
        std::cout << "Config is null" << std::endl;
        return cardsInfo;
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    const auto& cardsJson = Config["cards"];

    for (const std::string& category : categories)
    {
        if (!cardsJson.contains(category))
        {
            std::cout << "Unknown card category: " << category << std::endl;
            continue;
        }

        const auto& pool = cardsJson[category]["pool"];
        std::uniform_int_distribution<> dist(0, static_cast<int>(pool.size()) - 1);
        int pickIndex = dist(gen);

        const auto& card = pool[pickIndex];

        CardInfo info;
        info.id = card["id"].get<std::string>();
        info.title = card["title"].get<std::string>();
        info.description = card["description"].get<std::string>();
        info.statTag = card["statTag"].get<std::string>();
        info.value = card["value"].get<float>();
        info.icon = card["icon"].get<std::string>();
        info.vfxTag = card["vfxTag"].get<std::string>();

        if (cardsJson[category].contains("target"))
            info.target = cardsJson[category]["target"].get<std::string>();

        cardsInfo.push_back(info);
    }

    return cardsInfo;
}
