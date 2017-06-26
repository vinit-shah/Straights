#include "Player.h"

Player::Player(char c) : myScore(0) {
  if (c == 'h'){
    playerType = HUMAN;
  }
  else {
    playerType = COMPUTER;
  }
}

Player::~Player() {}

type Player::type() const
{
  return playerType;
}

void Player::play(const Card& card)
{
  for (const Card& c : myHand) {
    if (c == card){
      myHand.erase(c);
    }
  }
}

void Player::discard(const Card& card)
{
  for (Card c : myHand)
  {
    if (card == c){
      myHand.erase(c);
    }
  }
  myDiscardedPile.push_back(card);
  incrementScore(card.rank().rank());
}

void Player::rageQuit()
{
  playerType = COMPUTER;
}

void Player::deal(const std::vector<Card> & cards)
{
  myHand.clear();
  myDiscardedPile.clear();
  for (const Card& c : cards){
    myHand.push_back(c);
  }
}

const std::vector<Card>& Player::hand() const
{
  return myHand.cards();
}

const std::vector<Card>& Player::discarded() const
{
  return myDiscardedPile;
}

int Player::getScore() const
{
  return myScore;
}

//Protected Member Functions
void Player::incrementScore(int value)
{
  myScore = myScore + value;
}
