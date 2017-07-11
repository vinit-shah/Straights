#pragma once

#include <string>

class Model;

class Controller
{
    private:
        Model* myModel;
    
    public:
        Controller(Model*);

        void playCard(int cardNum);
        void endGame();
        void startGame(int seed, bool playerTypes[]);
        void endRound();
        void startRound();

        std::string roundResults() const;
        std::string gameResults() const;
};
