#pragma once

#include "Player.h"

class Computer : public Player
{
  public:
    Computer();
    virtual ~Computer();

    const Command play(const std::vector< std::vector <Card*> >& gameTable) override;

  private:
    void discard(const Card& card) override;
    void print(const std::vector< std::vector <Card*> >& gameTable) const override;
};
