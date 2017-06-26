#pragma once

#include <iostream>
#include <vector>

#include "Card.h"
#include "Command.h"

class Player
{
  public:
    enum type
    {
      HUMAN,
      COMPUTER
    } playerType;
    Player(char c);
    virtual ~Player();
    Player(const Player&) = delete;

    void play(const Card& card);
    void discard(const Card& card);
    void rageQuit();
    void deal(std::vector<Card>&);
    type type() const;
    const std::vector <Card>& hand() const;
    const std::vector<Card>& discarded() const;
    int getScore() const;

  protected:
    void incrementScore(int value);
  private:
    int                 myScore;
    std::vector<Card>   myHand;
    std::vector<Card>   myDiscardedPile;
};
