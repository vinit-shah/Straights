#pragma once
#include <vector>

#include "Card.h"

class Deck
{
public:
    Deck();
    ~Deck();
    const std::vector<Card*> cards(unsigned int start, unsigned int end) const;
    Card* find(const Card& card);
    void shuffle();
    void setSeed(int seed);

private:
    int mySeed;
    std::vector<Card*> myCards;
};
