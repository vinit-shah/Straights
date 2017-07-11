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
        void startRound(int seed);
        void rageQuit(int playerNum);
        
        const std::vector<Card*> getPlayerHand(int num) const;
        const std::vector<Card*> getPlayerDiscarded(int num) const;
        const std::vector<Card*> getCardsPlayed(Card::Suit) const;
        
        
        int getScore(int playerNum) const;
        int getDiscards(int playerNum) const;
        bool isCardLegal(Card*) const;
        bool isGameOver() const;
        bool isGameActive() const;
        bool isRoundOver() const;
};
