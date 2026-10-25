#pragma once

class StatupCard;

class CardManager
{

public:

	static CardManager* GetCardManager()
	{
		static CardManager DefaultCardManager;

		return &DefaultCardManager;
	};

	void SetupCards();
	void RemoveCards(CardInfo info);

	Delegate<> onCardSelected;
	
private:
	
	CardManager() {};

	std::shared_ptr<StatupCard> cardA;
	std::shared_ptr<StatupCard> cardB;
	std::shared_ptr<StatupCard> cardC;

};

