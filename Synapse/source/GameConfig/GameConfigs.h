#pragma once

#include "../Characters/Character.h"
#include "json.hpp"
#include <vector>

class GameConfigs
{

private:
	GameConfigs();

public:

	static GameConfigs& GetGameConfig();

	// Load Data
	std::map<std::string, Anim_Clip> GetCharacterData(std::string characterName);
	AbilityInfo GetCharacterAbilityData(std::string characterTag, std::string abilityName);
	std::vector<CardInfo> GetCardsData(std::vector<std::string> titles);

	nlohmann::json Config;

};

