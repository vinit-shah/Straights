#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>

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

void
Game::startRound()
{
    std::cout << "I'm here" << std::endl;
    std::cout << "A new round begins. It's player " << myCurrentPlayer+1 << "'s turn to play." <<std::endl;
    if (myPlayers[myCurrentPlayer]->getType() == Player::Type::COMPUTER)
        playCard(0);
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

void 
Game::playCard(int cardNum)
{
    Player* p = myPlayers[myCurrentPlayer];
    if (p->getType() == Player::Type::HUMAN)
    {
         
        Command c = p->play(myTable, cardNum);
        if (c.type == Command::Type::BAD_COMMAND)
        {
            return;
        }
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
            myCurrentPlayer = (myCurrentPlayer+1)%4;
        }
        else if(c.type == Command::Type::DISCARD) {
            std::cout << "Player " << myCurrentPlayer+1 << " discards " << c.card <<"." << std::endl;
            myCurrentPlayer = (myCurrentPlayer+1)%4;
        }
    }
    else 
    {
        while (p->getType() == Player::Type::COMPUTER && !isRoundOver())
        {
            Command c = p->play(myTable,0);
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
                myCurrentPlayer = (myCurrentPlayer+1)%4;
            }
            else if(c.type == Command::Type::DISCARD) {
                std::cout << "Player " << myCurrentPlayer+1 << " discards " << c.card <<"." << std::endl;
                myCurrentPlayer = (myCurrentPlayer+1)%4;
            }
            p = myPlayers[myCurrentPlayer];
        }
        
    }
}
void 
Game::rageQuit()
{
    Player* p = new Computer();
    p->clone(*myPlayers[myCurrentPlayer]);
    delete myPlayers[myCurrentPlayer];
    myPlayers[myCurrentPlayer] = p;
    playCard(0);
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
        std::cout << "size of hand " << p->hand().size() << std::endl;
        if(p->hand().size())
            return false;
    }
    return true;
}

const std::vector<Card*> Game::getPlayerHand () const
{
    return myPlayers[myCurrentPlayer]->hand();
}

const std::vector<Card*> Game::getPlayerDiscarded(int num) const
{
    return myPlayers[num]->discarded();
}

const std::vector<std::vector<Card*> > Game::getCardsPlayed() const
{
    return myTable;
}

int Game::currentPlayer() const 
{
    return myCurrentPlayer;
}

int Game::getScore(int num) const 
{
    return myPlayers[num]->score();
}

int Game::getDiscards(int num) const
{
    return myPlayers[num]->discarded().size();
}

std::string Game::roundResults() const 
{
    std::stringstream ss;
    for(int i = 0; i < myPlayers.size(); i++)
    {
        const Player* p = myPlayers[i];
        ss << "Player " << i+1 << "'s discards:";
        int old = p->score();
        const std::vector<Card*>&  discarded = p->discarded();
        for(const Card *c: discarded)
        {
            old -= c->rank().rank()+1;
            ss << " " << *c;
        }
        ss << std::endl;
        ss << "Player " << i+1 << "'s score: " << old << " + " << (p->score() - old) << " = " << p->score() << std::endl;
    }
    std::cout << ss.str() << std::endl;
    return ss.str();
}

std::string Game::gameResults() const
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
    std::stringstream ss;
    for (int i : minIndex)
    {
        ss << "Player " << i+1 << " wins!" << std::endl;
    }
    std::cout << ss.str() << std::endl;
    return ss.str();
}

std::string Game::getRoundInfo()
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
    std::stringstream ss;
    ss<< "A new round begins. It's player " << myCurrentPlayer+1 << "'s turn to play." <<std::endl;
    return ss.str();
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
