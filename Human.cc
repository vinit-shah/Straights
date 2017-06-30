#include <algorithm>
#include <iostream>
#include <string>

#include "Human.h"

Human::Human() : Player() {}

Human::~Human() {}

const Command
Human::play(const std::vector< std::vector <Card*> >& gameTable)
{
  print();
  std::vector <Card*> legalPlays = constructLegalPlays(gameTable);
  bool legal = false;
  Command c;
  while(!legal)
  {
      std::cin >> c;
      if (c.type == Command::Type::PLAY)
      {
        if(findCard(legalPlays, c.card))
        {
            legal = true;
            std::cout << "Player " << myCurrentPlayer << " plays " << c.card << std::endl;
            playCard(c.card);
        }
        else
            std::cout << "This is not a legal play." << std::endl;
      }
      else if (c.type == Command::Type::DISCARD)
      {
        if(legalPlays.empty())
        {
            legal = true;
            std::cout << "Player " << myCurrentPlayer << " discards " << c.card << std::endl;
            player->discard(c.card);
        }
        else
            std::cout << "You have a legal play. You may not discard." << std::endl;
      }
  }
  return c;
}

void
Human::print(const std::vector< std::vector<Card*> >& gameTable) const
{
  const std::string suits[4] = {"Clubs", "Diamonds", "Hearts", "Spades"};
  for(int i = 0; i < 4; ++i)
  {
      std::cout << suits[i];
      printCardList(gameTable[i]);
  }
  std::cout << "Your hand:";
  printCardList(myHand);
  std::cout << "Legal plays";
  std::vector<Card*> legalPlays = constructLegalPlays(gameTable);
  printCardList(legalPlays);
  std::cout << ">\n";
}

void
Human::discard(const Card& card)
{
  int index = findCard(myHand, card);
  myHand.erase(myHand.begin() + index);
}

void
Human::printCardList(const std::vector<Card*>& list) const
{
    for(const Card *c: list)
        std::cout << " " << *c;

    std::cout << std::endl;
}
