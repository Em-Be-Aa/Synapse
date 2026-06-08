#pragma once

#include "json.hpp"
#include "../Characters/Character.h"

class GameConfigs
{

private:
	GameConfigs();

public:

	static GameConfigs& GetGameConfig();

	// Load Data
	std::map<std::string, Anim_Clip> GetCharacterData(std::string characterName);

	nlohmann::json Config;

};

