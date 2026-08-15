#pragma once

#include "../Characters/Character.h"
#include "json.hpp"

class GameConfigs
{

private:
	GameConfigs();

public:

	static GameConfigs& GetGameConfig();

	// Load Data
	std::map<std::string, Anim_Clip> GetCharacterData(std::string characterName);
	AbilityCollisionInfo GetCharacterAbilityData(std::string characterTag, std::string abilityName);

	nlohmann::json Config;

};

