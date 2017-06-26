#pragma once

#include <vector>

#include "Deck.h"
#include "Player.h"

template <typename T>
using vector<T> = std::vector<T>;

class Game
{
public:
    Game();
    Game& Game(const Game&) = delete;
    Game& operator= (const Game&) = delete;
    void play();


private:
    vector<Player> myPlayers;
    vector<vector<Card>> myTable;
    unsigned int        myCurrentPlayer;
    Deck                myDeck;

    void startRound();
    void endRound();
    void constructLegalPlays();
    void pollNextPlayer();

    bool isRoundOver() const;
    bool isGameOver() const;

    void printWinners() const;
    void printCardList(const std::vector<Card>& ) const;
};
