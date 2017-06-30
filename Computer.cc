#include <algorithm>
#include <iostream>
#include <string>

#include "Computer.h"

Computer::Computer() : Player() {}

Computer::~Computer() {}

const Command
Computer::play(const std::vector< std::vector <Card*> >& gameTable)
{
  std::vector<Card*> legalPlays = constructLegalPlays(gameTable);
  Command command;
  if (legalPlays.empty())
  {
    command.type = Command::Type::DISCARD;
    command.card = *myHand[0];
    discard(*myHand[0]);
  }
  else
  {
    // std::cout << "computer" << std::endl;
    command.type = Command::Type::PLAY;
    playCard(*legalPlays[0]);
    command.card = *legalPlays[0];
  }
  return command;
}

void
Computer::discard(const Card& card)
{
  myDiscardedPile.push_back(myHand[0]);
  incrementScore(myHand[0]->rank().rank());
  myHand.erase(myHand.begin());
}

void
Computer::print(const std::vector< std::vector <Card*> >& gameTable) const
{
  return;
}
