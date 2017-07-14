#pragma once

#include <vector>
#include <string>

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
    void startGame(int seed, bool playerTypes[]);
    void startRound();
    void endRound();
    void playCard(int cardNum);
    void rageQuit();

    bool isGameOver() const;
    bool isRoundOver() const;
    bool isPlayLegal() const;

    const std::vector<Card*> getPlayerHand() const;
    const std::vector<Card*> getPlayerDiscarded(int num) const;
    const std::vector <std::vector<Card*> > getCardsPlayed() const;
    
    int currentPlayer() const;
    int getScore(int num) const;
    int getDiscards(int num) const;

    std::string roundResults() const;
    std::string gameResults() const;
    std::string getRoundInfo();

private:
    bool isLegal = true;
    std::vector<Player*> myPlayers;
    std::vector<std::vector<Card*> > myTable;
    unsigned int        myCurrentPlayer;
    Deck                myDeck;

    void pollNextPlayer();


    void printWinners() const;
    void printCardList(const std::vector<Card*>& ) const;
};
