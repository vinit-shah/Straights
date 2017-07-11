#include "Controller.h"
#include "Model.h"

Controller::Controller(Model* model) : myModel(model) {}

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

void Controller::startRound(int seed)
{
    myModel->startRound(seed);
}

void Controller::rageQuit(int playerNum)
{
    myModel->rageQuit(playerNum);
}

