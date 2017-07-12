#include <algorithm>
#include <iostream>
#include <string>

#include "Human.h"

Human::Human() : Player(), human(true) {}

Human::~Human() {}

const Command
Human::play(const std::vector< std::vector <Card*> >& gameTable, int cardNum)
{
    print(gameTable);
    std::vector <Card*> legalPlays = constructLegalPlays(gameTable);
    Command c;
    Card *card = myHand[cardNum];
    std::cout << "player chose card " << *card << std::endl;
    if (findCard(legalPlays,*card) != -1)
    {
        playCard(*card);
        std::cout << "command is of type play" << std::endl;
        c.type = Command::Type::PLAY;
        c.card = *card;
        return c;
    }
    else if (legalPlays.empty())
    {
        discard(*card);
        c.type = Command::Type::DISCARD;
        c.card = *card;
        return c;
    }
    c.type= Command::Type::BAD_COMMAND;
    std::cout << "retung bad command" << std::endl;
    return c;
}

bool 
Human::isHuman() const
{
    return human;
}

void
Human::rageQuit() 
{
    human = false;
}

void
Human::print(const std::vector< std::vector<Card*> >& gameTable) const
{
  const std::string suits[4] = {"Clubs", "Diamonds", "Hearts", "Spades"};
  std::cout << "Cards on the table:" << std::endl;
  for(int i = 0; i < 4; ++i)
  {
      std::cout << suits[i] << ":";
      printTableList(gameTable[i]);
  }
  std::cout << "Your hand:";
  printCardList(myHand);
  std::cout << "Legal plays:";
  std::vector<Card*> legalPlays = constructLegalPlays(gameTable);
  printCardList(legalPlays);
  std::cout << "> ";
}

void
Human::discard(const Card& card)
{
  int index = findCard(myHand, card);
  myDiscardedPile.push_back(myHand[index]);
  incrementScore(card.rank().rank()+1);
  myHand.erase(myHand.begin() + index);
}

void
Human::printTableList(const std::vector<Card*>& list) const
{
    for (const Card *c: list)
    {
        if(c!=nullptr)
            std::cout <<" " << c->rank().rank()+1;
    }
    std::cout << std::endl;
}

void
Human::printCardList(const std::vector<Card*>& list) const
{
    for(const Card *c: list)
        std::cout << " " << *c;

    std::cout << std::endl;
}
