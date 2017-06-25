#pragma once
#include <vector>

#include "Card.h"

class Deck
{
public:
    Deck();
    const std::vector<Card*> cards(unsigned int start, unsigned int end) const;
    
private:
    std::vector<Card*> myCards;
};
