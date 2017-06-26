#include <algorithm>

#include "Player.h"

Player::Player(char c) : myScore(0) {
  if (c == 'h'){
    playerType = Type::HUMAN;
  }
  else {
    playerType = Type::COMPUTER;
  }
}

Player::~Player() {}

Player::Type Player::type() const
{
  return playerType;
}

int Player::findCard(const std::vector<Card*> v, const Card* c)
{
  int ret = -1;
    for(int i = 0; i < v.size(); ++i)
    {
        const Card* card = v[i];
        if(*c == *card)
            return i;
    }
    return ret;
}

void Player::play(const Card* card)
{
  auto it = findCard(myHand, card);
  myHand.erase(myHand.begin() + it);
}

void Player::discard(const Card* card)
{
  auto it = findCard(myHand, card);
  myDiscardedPile.push_back(myHand[it]);
  myHand.erase(myHand.begin() + it);
  incrementScore(card->rank().rank());
}

void Player::rageQuit()
{
  playerType = Type::COMPUTER;
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
void Player::incrementScore(int value)
{
  myScore = myScore + value;
}
