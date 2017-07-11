#include "Model.h"

Model::Model() {}

void Model::startGame(int seed, bool playerTypes[])
{
    myGame = new Game();
    myGame->startGame(seed,playerTypes);
    notify();
}

void Model::startRound()
{
    myGame->startRound();
    notify();
}

void Model::endGame()
{
    delete myGame;
    myGame = nullptr;
    notify(); 
}

void Model::endRound()
{
    myGame->endRound();
    notify();
}

const std::vector<Card*> Model::getPlayerHand(int num) const 
{
    return myGame->getPlayerHand(num);
}

const std::vector<Card*> Model::getPlayerDiscarded(int num) const
{
    return myGame->getPlayerDiscarded(num);
}

const std::vector<Card*> Model::getCardsPlayed(Card::Suit suit) const
{
    return myGame->getCardsPlayed(suit);
}

int Model::getScore(int playerNum) const
{
    return myGame->getScore(playerNum);
}

int Model::getDiscards(int playerNum) const
{
    return myGame->getDiscards(playerNum);
}

bool Model::isCardLegal(Card* card) const
{
    return true; //myGame->isCardLegal(card);
}

bool Model::isGameOver() const 
{
    return myGame->isGameOver();
}

bool Model::isGameActive() const
{
    return nullptr== myGame;
}

bool Model::isRoundOver() const
{
    return myGame->isRoundOver();
}

