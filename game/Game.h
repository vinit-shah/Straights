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
    void startGame(int seed, bool playerTypes[]);
    void startRound();
    void rageQuit(int playerNum);
    void endRound();
    bool isRoundOver() const;
    bool isCardLegal(Card*) const;
    const std::vector<Card*> getPlayerhand(int num) const;
    const std::vector<Card*> getPlayerDiscarded(int num) const;
    const std::vector<Card*> getCardsPlayed(Card::Suit) const;
    int currentPlayer() const;

private:
    std::vector<Player*> myPlayers;
    std::vector<std::vector<Card*> > myTable;
    unsigned int        myCurrentPlayer;
    Deck                myDeck;

    void computerPlay(Player *player, const std::vector<Card*> &legalPlays);
    void humanPlay(Player *player, const std::vector<Card*> &legalPlays);
    void pollNextPlayer();


    void printWinners() const;
    void printCardList(const std::vector<Card*>& ) const;
};
