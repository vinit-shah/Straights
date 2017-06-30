#include <algorithm>
#include <iostream>
#include <string>

#include "Computer.h"

Computer::Computer() : Player() {}

Computer::~Computer() {}

const Command
Computer::play(const std::vector< std::vector <Card*> >& gameTable)
{
    std::cout << "computer is playing" << std::endl;
  std::vector<Card*> legalPlays = constructLegalPlays(gameTable);
  Command command;
  if (legalPlays.empty())
  {
    discard(*myHand[0]);
    command.type = Command::Type::DISCARD;
  }
  else
  {
    // std::cout << "computer" << std::endl;
    bool first = false;
    Command command;
    command.type = Command::Type::PLAY;
    for (Card* c : myHand)
    {
      if (c->rank().rank() == 6 && c->suit().suit() == 3)
      {
        command.card = Card(6,3);
        playCard(command.card);
        first = true;
      }
    }
    if (!first)
    {
      playCard(*legalPlays[0]);
      command.card = *legalPlays[0];
    }
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
