#pragma once

#include <string>

class Model;

class Controller
{
    private:
        Model* myModel;
    
    public:
        Controller(Model*);

        void endGame();
        void startGame(int seed, bool playerTypes[]);
        void endRound();
        void startRound(int seed);
        void rageQuit(int);
};
