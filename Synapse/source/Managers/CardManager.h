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

	StatupCard* cardA;
	StatupCard* cardB;
	StatupCard* cardC;

};

