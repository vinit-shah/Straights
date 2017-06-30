#pragma once

#include "Player.h"

class Human : public Player
{
  public:
    Human();
    virtual ~Human();

    const Command play(const std::vector< std::vector <Card*> >& gameTable) override;

  private:
    void print(const std::vector< std::vector <Card*> >& gameTable) const override;
    void discard(const Card& card) override;
    void printCardList(const std::vector<Card*>& list) const;
};
