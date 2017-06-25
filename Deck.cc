#include "Deck.h"

Deck::Deck()
{
    myCards.reserve(52);
    for(int i = 0; i < Card::Rank::MAX_SUIT; ++i)
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
