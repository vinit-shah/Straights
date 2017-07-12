#include "Model.h"

Model::Model() : myGame(nullptr) {}

void Model::startGame(int seed, bool playerTypes[])
{
    if (isGameActive())
    {
        std::cout << "here" << std::endl;
        delete myGame;
    }
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

void Model::playCard(int cardNum)
{
    myGame->playCard(cardNum);
    notify();
}

void Model::rageQuit()
{
    myGame->rageQuit();
}

std::string Model::roundResults() const
{
    return myGame->roundResults();
}

std::string Model::gameResults() const
{
    return myGame->gameResults();
}

const std::vector<Card*> Model::getPlayerHand() const 
{
    return myGame->getPlayerHand();
}

const std::vector<Card*> Model::getPlayerDiscarded(int num) const
{
    return myGame->getPlayerDiscarded(num);
}

const std::vector <std::vector<Card*> > Model::getCardsPlayed() const
{
    return myGame->getCardsPlayed();
}

int Model::getActivePlayer() const
{
    return myGame->currentPlayer();
}

int Model::getScore(int playerNum) const
{
    return myGame->getScore(playerNum);
}

int Model::getDiscards(int playerNum) const
{
    return myGame->getDiscards(playerNum);
}

bool Model::isGameOver() const 
{
    return myGame->isGameOver();
}

bool Model::isGameActive() const
{
    return nullptr != myGame;
}

bool Model::isRoundOver() const
{
    return myGame->isRoundOver();
}

