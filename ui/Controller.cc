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
}

void Controller::endRound() 
{
    myModel->endGame();
}

void Controller::startRound()
{
    myModel->startRound();
}

void Controller::rageQuit()
{
    myModel->rageQuit();
}

