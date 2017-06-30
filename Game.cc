#include <algorithm>
#include <iostream>
#include <string>

#include "Game.h"

Game::Game()
{
    myTable.resize(4);
}

Game::~Game()
{
    for (Player * p : myPlayers)
    {
      delete p;
    }
    myPlayers.resize(0);
}

void Game::startGame()
{
  for (int i = 0; i < 4; i++)
  {
    char x;
    std::cout << "Is player " << i << " a human(h) or a computer(c)?\n";
    std::cin >> x;
    Player* p = i == 'h' ? new HumanPlayer() : new ComputerPlayer();
    myPlayers.push_back(p);
  }
}

void Game::play()
{
    while(!isGameOver())
    {
        std::cout << "Starting round" << std::endl;
        startRound();
        while(!isRoundOver())
        {
            // std::cout << "polling player " << std::endl;
            pollNextPlayer();
        }
        endRound();
        std::cout << "ending round" << std::endl;
    }
    printWinners();
}


void
Game::pollNextPlayer()
{
    Player* p = myPlayers[myCurrentPlayer];
    const std::vector<Card*> &hand = p->hand();
    std::vector<Card*> legalPlays;
    if( p->type() == Player::Type::HUMAN)
    {
        const std::string suits[4] = {"Clubs", "Diamonds", "Hearts", "Spades"};
        for(int i = 0; i < 4; ++i)
        {
            std::cout << suits[i];
            printCardList(myTable[i]);
        }
        std::cout << "Your hand:";
        printCardList(p->hand());
        std::cout << "Legal plays";
        constructLegalPlays(hand, legalPlays);
        printCardList(legalPlays);
        std::cout << ">\n";
        humanPlay(p, legalPlays);
    }
    else if ( p->type() == Player::Type::COMPUTER)
    {
        // std::cout << "computer" << std::endl;
        constructLegalPlays(hand,legalPlays);
        computerPlay(p,legalPlays);
    }
    myCurrentPlayer = (myCurrentPlayer+1)%4;
}

static bool findCard(const std::vector<Card*> v, const Card* c)
{
    for(const Card* card : v)
    {
        if(*c == *card)
            return true;
    }
    return false;
}

void
Game::humanPlay(Player*player, const std::vector<Card*> &legalPlays)
{
    const std::vector<Card*> &hand = player->hand();
    bool legal = false;
    while(!legal)
    {
        Command c;
        std::cin >> c;
        switch(c.type)
        {
            case Command::Type::PLAY:
                if(findCard(legalPlays, &c.card))
                {
                    legal = true;
                    std::cout << "Player " << myCurrentPlayer << " plays " << c.card << std::endl;
                    player->play(&c.card);
                    Card* temp;
                    for (Card* runner : legalPlays)
                    {
                      if (*runner == c.card)
                          temp = runner;
                    }
                    int suit = temp->suit().suit();
                    int rank = temp->rank().rank();

                    if (myTable[suit].empty())
                        myTable[suit].push_back(temp);
                    else if (myTable[suit].front()->rank().rank() > rank)
                        myTable[suit].insert(myTable[suit].begin(),temp);
                    else
                        myTable[suit].push_back(temp);
                }
                else
                    std::cout << "This is not a legal play." << std::endl;
                break;
            case Command::Type::DISCARD:
                if(legalPlays.empty())
                {
                    legal = true;
                    std::cout << "Player " << myCurrentPlayer << " discards " << c.card << std::endl;
                    player->discard(&c.card);
                }
                else
                    std::cout << "You have a legal play. You may not discard." << std::endl;
                break;
            case Command::Type::DECK:
                for(int i = 0; i < 4; i++)
                    printCardList(myDeck.cards(i*13,(i+1)*13));
                break;
            case Command::Type::QUIT:
                std::cout << "Need to implement exception throw once main is written" << std::endl;
                // throw exception to quit
                break;
            case Command::Type::RAGEQUIT:
                {
                    std::cout << "Player " << myCurrentPlayer << " ragequits. A computer will now take over." << std::endl;
                    Player *newPlayer = new ComputerPlayer();
                    *newPlayer = std::move(*player);
                    delete player;
                    myPlayers[myCurrentPlayer] = newPlayer;
                }
                return;
            default:
                std::cout << "!!!!!!!!!uh this shouldnt happen :))!!!!!!!!!" << std::endl;
                break;
        }
    }
}

void
Game::computerPlay(Player* p, const std::vector<Card*> & legalPlays)
{
    if (legalPlays.empty())
    {
      p->discard(p->hand()[0]);
    }
    else
    {
      std::cout << "computer" << std::endl;
      bool first = false;
      for (Card* c : p->hand())
      {
        if (c->rank().rank() == 6 && c->suit().suit() == 3)
        {
          p->play(c);
          myTable[3].push_back(c);
          first = true;
        }
      }
      if (!first)
      {
        p->play(legalPlays[0]);
        std::cout << "played " << *legalPlays[0] << std::endl;
        int suit = legalPlays[0]->suit().suit();
        int rank = legalPlays[0]->rank().rank();
        if (myTable[suit].empty()){
          myTable[suit].push_back(legalPlays[0]);
        }
        else if (myTable[suit].front()->rank().rank() > rank)
        { //put the card in the front
          myTable[suit].insert(myTable[suit].begin(),legalPlays[0]);
        }
        else
        {
          myTable[suit].push_back(legalPlays[0]);
        }
      }
    }
}

void
Game::constructLegalPlays(const std::vector<Card*> &hand, std::vector<Card*>& plays)
{
    for (Card* c : hand)
    {
        if (*c == Card(Card::Rank(6), Card::Suit(0)) || *c == Card(Card::Rank(6), Card::Suit(1)) ||
            *c == Card(Card::Rank(6), Card::Suit(2)) || *c == Card(Card::Rank(6), Card::Suit(3)))
            plays.push_back(c);

        for (const std::vector<Card*>& v : myTable)
        {
            // std::cout << "card rank " << c->rank().rank() << std::endl;
            if (!v.empty() && v[0]->suit().suit() == c->suit().suit())
            {
                Card *front = v[0];
                // std::cout << "front " << front->rank().rank() << std::endl;
                if (front->rank().rank() == c->rank().rank() + 1)
                    plays.push_back(c);
                else
                {
                    Card *back = v.back();
                    // std::cout << "back " << back->rank().rank() << std::endl;
                    if (back->rank().rank() == c->rank().rank() - 1)
                        plays.push_back(c);
                }
            }
        }
    }
}

void
Game::startRound()
{
    //myDeck = myLastDeck;
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
        std::cout << "Player " << i << "'s discards:";
        int old = p->score();
        const std::vector<Card*>&  discarded = p->discarded();
        for(const Card *c: discarded)
        {
            old -= c->rank().rank();
            std::cout << " " << *c;
        }
        std::cout << std::endl;
        std::cout << "Player " << i << "'s score: " << old << " + " << (p->score() - old) << " = " << p->score() << std::endl;
    }
}

void
Game::printWinners() const
{
    for(int i = 0; i < myPlayers.size(); ++i)
    {
        const Player* p = myPlayers[i];
        std::cout << "Player's score is " << p->score() << std::endl;
    }
}

void
Game::printCardList(const std::vector<Card*>& list) const
{
    for(const Card *c: list)
        std::cout << " " << *c;

    std::cout << std::endl;
}
