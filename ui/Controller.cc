#include "Controller.h"
#include "Model.h"

Controller::Controller(Model* model) : myModel(model) {}

void Controller::playCard(int cardNum)
{
    myModel->playCard(cardNum);
}

void Controller::endGame() 
{
    myModel->endGame();
}

void Controller::startGame(int seed, bool playerTypes[])
{
    myModel->startGame(seed,playerTypes);
    startRound();
}

void Controller::endRound() 
{
    myModel->endGame();
}

void Controller::startRound()
{
    myModel->startRound();
}

std::string Controller::roundResults() const
{
    return myModel->roundResults();
}

std::string Controller::gameResults() const
{
    return myModel->gameResults();
}
