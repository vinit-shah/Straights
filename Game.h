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
    play();

private:
    vector<Player> myPlayers;
    vector<vector<Card>> myTable;
    unsigned int        myCurrentPlayer;
    Deck                myDeck;

    void pollNextPlayer();
    bool isGameOver();
    void printWinners();
};
