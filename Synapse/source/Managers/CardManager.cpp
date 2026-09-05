#include "../Characters/Player.h"
#include "../Game/Game.h"
#include "../Game/Session.h"
#include "../GameConfig/GameConfigs.h"
#include "../Templates/Templates.h"
#include "../UI/Game/StatupCard.h"
#include "CardManager.h"
#include <random>
#include <string>
#include <vector>

void CardManager::SetupCards()
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

	cardA = SpawnActor<StatupCard>(cardsInfo[0], -250.0f );
	cardB = SpawnActor<StatupCard>(cardsInfo[1],  0.0f   );
	cardC = SpawnActor<StatupCard>(cardsInfo[2],  250.0f );

	cardA->OnClicked.Subscribe
	(
		[this]() { RemoveCards(cardA->GetCardInfo()); }
	);

	cardB->OnClicked.Subscribe
	(
		[this]() { RemoveCards(cardB->GetCardInfo()); }
	);

	cardC->OnClicked.Subscribe
	(
		[this]() { RemoveCards(cardC->GetCardInfo()); }
	);
}

void CardManager::RemoveCards(CardInfo info)
{
	// Modify the vitals first
	Game::GetGame()->GetCurrentSession()->GetActivePlayer()->GetVitalsComponent().ModifyVital(info.target, info.statTag, info.value, info.isMultiplier);

	// Send delegate to HUD next
	onCardSelected.Broadcast();

	// Then remove the UI
	cardA->Destroy();
	cardB->Destroy();
	cardC->Destroy();
}
