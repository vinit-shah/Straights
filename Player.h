#pragma once

#include <iostream>
#include <vector>

#include "Card.h"
#include "Command.h"

class Player
{
  public:
    enum class Type
    {
      HUMAN,
      COMPUTER
    } playerType;
    Player(char c);
    virtual ~Player();
    Player(const Player&) = delete;

    int findCard(const std::vector<Card*> v, const Card* c);
    void play(const Card* card);
    void discard(const Card* card);
    void rageQuit();
    void deal(const std::vector<Card*>&);
    Type type() const;
    const std::vector <Card*>& hand() const;
    const std::vector<Card*>& discarded() const;
    int score() const;

  private:
    int                  myScore;
    std::vector<Card*>   myHand;
    std::vector<Card*>   myDiscardedPile;

    void incrementScore(int value);
};
