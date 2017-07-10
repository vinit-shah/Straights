#include <random>
#include "Deck.h"

Deck::Deck()
{
    mySeed = 0;
    myCards.reserve(52);
    for(int i = 0; i < Card::Suit::MAX_SUIT; ++i)
    {
        for(int j = 0; j < Card::Rank::MAX_RANK; ++j)
            myCards.push_back(new Card(j, i));
    }
}

Deck::~Deck()
{
    for(Card* card : myCards)
        delete card;
}

const std::vector<Card*>
Deck::cards(unsigned int start, unsigned int end) const
{
    return std::vector<Card*>(myCards.begin() + start, myCards.begin() + end);
}

Card*
Deck::find(const Card& card)
{
    for(Card *c : myCards)
    {
        if(*c == card)
            return c;
    }
    return nullptr;
}

void 
Deck::setSeed(int seed)
{
    mySeed = seed;
}

void
Deck::shuffle() {
  static std::mt19937 rng(mySeed);

	int n = 52;

	while ( n > 1 ) {
		int k = (int) (rng() % n);
		--n;
		Card *c = myCards[n];
		myCards[n] = myCards[k];
		myCards[k] = c;
	}
}
