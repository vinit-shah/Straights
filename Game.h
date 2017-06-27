#pragma once

#include <vector>

#include "Command.h"
#include "Deck.h"
#include "Player.h"

class Game
{
public:
    Game();
    ~Game();
    Game(const Game&) = delete;
    Game& operator= (const Game&) = delete;
    void play();
    void startGame();


private:
    std::vector<Player*> myPlayers;
    std::vector<std::vector<Card*>> myTable;
    unsigned int        myCurrentPlayer;
    Deck                myDeck;

    void computerPlay(Player *player, const std::vector<Card*> &legalPlays);
    void humanPlay(Player *player, const std::vector<Card*> &legalPlays);
    void startRound();
    void endRound();
    void constructLegalPlays(const std::vector<Card*> &hand, std::vector<Card*>& plays);
    void pollNextPlayer();

    bool isRoundOver() const;
    bool isGameOver() const;

    void printWinners() const;
    void printCardList(const std::vector<Card*>& ) const;
};
