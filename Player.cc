#include <algorithm>

#include "Player.h"

Player::Player() : myScore(0) {}

Player::~Player() {}

Player& (Player && player)
{
    myHand = std::move(myHand,player.myHand);
    myDiscardedPile = std::move(myDiscardedPile,player.myDiscardedPile);
    myScore = std::move(myScore,player.myScore);
    return *this;
}

void Player::deal(const std::vector<Card*> & cards)
{
  myHand.clear();
  myDiscardedPile.clear();
  for (Card* c : cards){
    myHand.push_back(c);
  }
}

const std::vector<Card*>& Player::hand() const
{
  return myHand;
}

const std::vector<Card*>& Player::discarded() const
{
  return myDiscardedPile;
}

int Player::score() const
{
  return myScore;
}

//Protected Member Functions
int
Player::findCard(const std::vector<Card*>& v, const Card& c)
{
  int ret = -1;
    for(int i = 0; i < v.size(); ++i)
    {
        if(*v[i] == card)
            return i;
    }
    return ret;
}

void
Player::incrementScore(int value)
{
  myScore = myScore + value;
}

void
Player::playCard(const Card& card)
{
  int index = findCard(myHand,card);
  myHand.erase(myHand.begin() + index);
}

std::vector<Card*> constructLegalPlays(const std::vector< std::vector <Card*> >& gameTable)
{
  std::vector<Card*> plays;
  for (Card* c : myHand)
  {
      if (*c == Card(Card::Rank(6), Card::Suit(0)) || *c == Card(Card::Rank(6), Card::Suit(1)) ||
          *c == Card(Card::Rank(6), Card::Suit(2)) || *c == Card(Card::Rank(6), Card::Suit(3)))
          plays.push_back(c);

      for (const std::vector<Card*>& v : gameTable)
      {
          // std::cout << "card rank " << c->rank().rank() << std::endl;
          if (!v.empty() && v[0]->suit().suit() == c->suit().suit())
          {
              Card *front = v[0];
              // std::cout << "front " << front->rank().rank() << std::endl;
              if (front->rank().rank() == c->rank().rank() + 1)
                  plays.push_back(c);
              else
              {
                  Card *back = v.back();
                  // std::cout << "back " << back->rank().rank() << std::endl;
                  if (back->rank().rank() == c->rank().rank() - 1)
                      plays.push_back(c);
              }
          }
      }
  }
  return plays;
}
