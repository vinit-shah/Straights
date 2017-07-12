#pragma once

#include <vector>
#include <string>

#include "Subject.h"
#include "../game/Card.h"
#include "../game/Game.h"

class Model : public Subject 
{
    private:
        Game* myGame;
    
    public:
        Model();

        void startGame(int seed, bool playerTypes[]);
        void endGame();
        void endRound();
        void startRound();
        void playCard(int cardNum);
        void rageQuit();

        std::string roundResults() const;
        std::string gameResults() const;
        std::string getRoundInfo() const;

        const std::vector<Card*> getPlayerHand() const;
        const std::vector<Card*> getPlayerDiscarded(int num) const;
        const std::vector <  std::vector<Card*> > getCardsPlayed() const;
        
        int getActivePlayer() const;
        int getScore(int playerNum) const;
        int getDiscards(int playerNum) const;
        
        bool isGameOver() const;
        bool isGameActive() const;
        bool isRoundOver() const;
};
