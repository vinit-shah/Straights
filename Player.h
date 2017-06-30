#pragma once

#include <iostream>
#include <vector>

#include "Card.h"
#include "Command.h"

class Player
{
  public:
    Player();
    virtual ~Player();
    Player(const Player&) = delete;
    Player&(Player&&);

    void deal(const std::vector<Card*>&);
    const std::vector <Card*>& hand() const;
    const std::vector<Card*>& discarded() const;
    int score() const;

    virtual const Command play(const std::vector< std::vector <Card*> >& gameTable) = 0;

  protected:
    int                  myScore;
    std::vector<Card*>   myHand;
    std::vector<Card*>   myDiscardedPile;

    int findCard(const std::vector<Card*>& v, const Card& c);
    void incrementScore(int value);
    void playCard(const Card& card);

    virtual void discard(const Card& card) = 0;
    virtual void print(const std::vector< std::vector <Card*> >& gameTable) const = 0;
    std::vector<Card*> constructLegalPlays(const std::vector< std::vector <Card*> >& gameTable);
};
