#pragma once

#include "Player.h"

class Computer : public Player
{
  public:
    Computer();
    virtual ~Computer();
    virtual bool isHuman() const;
    const Command play(const std::vector< std::vector <Card*> >& gameTable, int cardNum) override;
    virtual void rageQuit() override;
  private:
    void discard(const Card& card) override;
    void print(const std::vector< std::vector <Card*> >& gameTable) const override;
};
