#include <algorithm>
#include <iostream>
#include <string>

#include "Game.h"
#include "Human.h"
#include "Computer.h"

Game::Game()
{
    myTable.resize(4);
}

Game::~Game()
{
    for (Player * p : myPlayers)
        delete p;

    myPlayers.resize(0);
}

void Game::startGame(int seed, bool playerTypes[])
{
  myDeck.setSeed(seed);
  for (int i = 0; i < 4; i++)
  {
    Player* p;
    if(playerTypes[i])
        p = new Human();
    else
        p = new Computer();
    myPlayers.push_back(p);
  }
}

void Game::play()
{
    while(!isGameOver())
    {
        startRound();
        while(!isRoundOver())
        {
            try
            {
                pollNextPlayer();
            }
            catch(std::exception & e)
            {
                throw e;
            }
        }
        endRound();
    }
    printWinners();
}

int Game::currentPlayer() const 
{
    return myCurrentPlayer;
}

void
Game::pollNextPlayer()
{
    Player* p = myPlayers[myCurrentPlayer];
    Command c = p->play(myTable);
    if(c.type == Command::Type::PLAY)
    {
        Card * card = myDeck.find(c.card);
        int s = card->suit().suit();
        if (myTable[s].empty())
            myTable[s].push_back(card);
        else if (myTable[s].front()->rank().rank() > card->rank().rank())
            myTable[s].insert(myTable[s].begin(), card);
        else
            myTable[s].push_back(card);
        std::cout << "Player " << myCurrentPlayer+1 <<  " plays " << c.card << "."<< std::endl;
    }
    else if(c.type == Command::Type::DISCARD)
        std::cout << "Player " << myCurrentPlayer+1 << " discards " << c.card <<"." << std::endl;
    else if(c.type ==  Command::Type::DECK)
    {
        for(int i = 0; i < 4; i++)
            printCardList(myDeck.cards(i*13,(i+1)*13));
    }
    else if(c.type == Command::Type::QUIT)
        throw std::exception();
    else if(c.type == Command::Type::RAGEQUIT)
    {
        std::cout << "Player " << myCurrentPlayer+1 << " ragequits. A computer will now take over." << std::endl;
        Player *newPlayer = new Computer();
        newPlayer->clone(*p);
        delete p;
        myPlayers[myCurrentPlayer] = newPlayer;
        pollNextPlayer();
        return;
    }
    myCurrentPlayer = (myCurrentPlayer+1)%4;
}

void
Game::startRound()
{
    myDeck.shuffle();

    for(std::vector<Card*>& list:myTable)
        list.clear();

    for(int i = 0; i < myPlayers.size(); ++i)
    {
        Player* p = myPlayers[i];
        const std::vector<Card*>& cards = myDeck.cards(i*13, (i+1)*13);
        for(const Card *c: cards)
        {
            if(c->suit().suit() == Card::Suit::SPADE
                && c->rank().rank() == Card::Rank::SEVEN)
                myCurrentPlayer = i;
        }
        p->deal(cards);
    }
    std::cout << "A new round begins. It's player " << myCurrentPlayer+1 << "'s turn to play." <<std::endl;
}

bool
Game::isGameOver() const
{
    for(const Player* p: myPlayers)
    {
        if(p->score() >= 80)
            return true;
    }
    return false;
}

bool
Game::isRoundOver() const
{
    for(const Player* p: myPlayers)
    {
        if(p->hand().size())
            return false;
    }
    return true;
}

void
Game::endRound()
{
    for(int i = 0; i < myPlayers.size(); i++)
    {
        const Player* p = myPlayers[i];
        std::cout << "Player " << i+1 << "'s discards:";
        int old = p->score();
        const std::vector<Card*>&  discarded = p->discarded();
        for(const Card *c: discarded)
        {
            old -= c->rank().rank()+1;
            std::cout << " " << *c;
        }
        std::cout << std::endl;
        std::cout << "Player " << i+1 << "'s score: " << old << " + " << (p->score() - old) << " = " << p->score() << std::endl;
    }
}

const std::vector<Card*> Game::getPlayerHand (int num) const
{
    return myPlayers[num].hand();
}

const std::vector<Card*> Game::getPlayerDiscarded(int num) const
{
    return myPlayers[num].discarded();
}

const std::vector<Card*> Game::getCardsPlayed(Card::Suit suit) const
{
    return myTable[suit.suit()];
}

int Game::getScore (int playerNum) const 
{
    return myPlayers[playerNum].score();
}

int Game::getDiscards(int playerNum) const
{
    return myPlayers[playerNum].discarded().size();
}

void
Game::printWinners() const
{
    std::vector<int> minIndex;
    int minScore = 100000000;
    for(int i = 0; i < myPlayers.size(); ++i)
    {
        if (myPlayers[i]->score() < minScore)
        {
            minIndex.clear();
            minIndex.push_back(i);
            minScore = myPlayers[i]->score();
        }
        else if (myPlayers[i]->score() == minScore)
        {
            minIndex.push_back(i);
        }
    }
    for (int i : minIndex)
    {
        std::cout << "Player " << i+1 << " wins!" << std::endl;
    }
}

void
Game::printCardList(const std::vector<Card*>& list) const
{
    for(const Card *c: list)
        std::cout << " " << *c;

    std::cout << std::endl;
}
