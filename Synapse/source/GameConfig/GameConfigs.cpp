#include "../Managers/SynapseFunctionLibrary.h"
#include "GameConfigs.h"
#include <iostream>
#include <optional>
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
AbilityInfo GameConfigs::GetCharacterAbilityData(std::string characterTag, std::string abilityName)
{
    AbilityInfo characterAbility;

    if (Config != nullptr)
    {
        auto& ability = Config[characterTag]["abilities"][abilityName];

        if (!ability.is_null())
        {
            if (ability.contains("collidorSize"))
            {
                glm::vec2 collidorSize = { ability["collidorSize"]["x"].get<float>(), ability["collidorSize"]["y"].get<float>() };
                characterAbility.collidorSize = collidorSize;
            }
            else
            {
                characterAbility.collidorSize = std::nullopt;
            }

            if (ability.contains("collidorOffset"))
            {
                glm::vec2 collidorOffset = { ability["collidorOffset"]["x"].get<float>(), ability["collidorOffset"]["y"].get<float>() };
                characterAbility.collidorOffset = collidorOffset;
            }
            else
            {
                characterAbility.collidorOffset = std::nullopt;
            }

            if (ability.contains("dashDistance"))
            {
                float dashDistance = ability["dashDistance"].get<float>();
                characterAbility.dashDistance = dashDistance;
            }
            else
            {
                characterAbility.dashDistance = std::nullopt;
            }
            
            float abilityDamage = ability["abilityDamage"].get<float>();
            float abilityCooldown = ability["abilityCooldown"].get<float>();
         
            
            
            characterAbility.abilityDamage = abilityDamage;
            characterAbility.abilityCooldown = abilityCooldown;
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
    std::vector<std::string> usedIds; // tracks picks across this whole draft

    for (const std::string& category : categories)
    {
        if (!cardsJson.contains(category))
        {
            std::cout << "Unknown card category: " << category << std::endl;
            continue;
        }

        const auto& pool = cardsJson[category]["pool"];

        // Build a list of indices whose id hasn't already been used this draft
        std::vector<int> availableIndices;
        for (int i = 0; i < static_cast<int>(pool.size()); i++)
        {
            std::string candidateId = pool[i]["id"].get<std::string>();
            if (std::find(usedIds.begin(), usedIds.end(), candidateId) == usedIds.end())
            {
                availableIndices.push_back(i);
            }
        }

        if (availableIndices.empty())
        {
            std::cout << "No unused cards left in category: " << category << std::endl;
            continue; // every card in this category's pool is already used this draft
        }

        std::uniform_int_distribution<> dist(0, static_cast<int>(availableIndices.size()) - 1);
        int pickIndex = availableIndices[dist(gen)];
        const auto& card = pool[pickIndex];

        CardInfo info;
        info.id = card["id"].get<std::string>();
        info.title = card["title"].get<std::string>();
        info.description = card["description"].get<std::string>();
        info.statTag = card["statTag"].get<std::string>();
        info.value = card["value"].get<float>();
        info.isMultiplier = card["isMultiplier"].get<bool>();
        info.icon = card["icon"].get<std::string>();
        info.vfxTag = card["vfxTag"].get<std::string>();

        if (cardsJson[category].contains("target"))
            info.target = cardsJson[category]["target"].get<std::string>();

        usedIds.push_back(info.id);
        cardsInfo.push_back(info);
    }

    return cardsInfo;
}