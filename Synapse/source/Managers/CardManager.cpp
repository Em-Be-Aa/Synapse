#include "../GameConfig/GameConfigs.h"
#include "../Templates/Templates.h"
#include "../UI/Game/StatupCard.h"
#include "CardManager.h"
#include <random>
#include <string>
#include <vector>

void CardManager::ComputeRandomCards()
{
	std::vector<std::string> Cards = {"VITALS", "SLASH", "IMPACT", "SURGE"};
	std::vector<std::string> selectedCards;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::discrete_distribution<> dist({ 40, 30, 20, 10 });

	for (size_t i = 0; i < 3; i++)
	{
		int index = dist(gen);
		selectedCards.push_back(Cards[index]);
	}

	std::vector<CardInfo> cardsInfo = GameConfigs::GetGameConfig().GetCardsData(selectedCards);

	SpawnActor<StatupCard>(cardsInfo[0]);

}
