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
        void startGame();
        void endRound();
        void startRound();
        void rageQuit(int);
}

