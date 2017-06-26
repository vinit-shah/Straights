#include <iostream>
#include <string>
#include "Game.h"

Game::Game()
{
    // we only have 4 suits
    myTable.reserve(4);
}

void Game::play()
{
    while(!isGameOver())
    {
        startRound();
        while(!isRoundOver())
            pollNextPlayer();
        endRound();
    }
    printWinners();
}


void
Game::pollNextPlayer()
{
    Player& p = myPlayers[myCurrentPlayer];
    const std::vector<Card> &hand = p.hand();
    std::vector<Card> &legalPlays;
    if( p.type() == Player::Type::Human)
    {
        static const std::string suits[4] = {"Clubs", "Diamonds", "Hearts", "Spades"};
        for(int i = 0; i < 4; ++i)
        {
            std::cout << suits[i];
            printCardList(myTable(i));
        }
        std::cout << "Your hand:";
        printCardList(p.hand());
        std::cout << "Legal plays";
        constructLegalPlays(hand, legalPlays);
        printCardList(legalPlays);
        humanPlay(p, legalPlays);
    }
    else if ( p.type() == Player::Type::COMPUTER)
    {
        const std::vector <Card> &hand = p.hand();
        std:: vector <Card> legalPlays;
        constructLegalPlays(hand,legalPlays);
        if (legalPlays.empty())
        {
          p.discard(hand[0]);
        }
        else
        {
          p.play(legalPlays[0]);
          int suit = legalPlays[0].suit().suit();
          int rank = legalPlays[0].rank().rank();
          std::vector<Card>::iterator it = myTable[suit].begin();
          for (; myTable[suit].end() != it; ++it)
          {
            if (it.rank().rank() < rank)
            {
              break;
            }
          }
          myTable[suit].insert(it,legalPlays[0]);
        }
    }
    myCurrentPlayer++;
}

Command
Game::getCommand()
{
    Command c;
    Card card;
    std::cin >> c;
    if(c.command != Command::Type::PLAY && c.command != Command::Type::DISCARD)
        return c;
    std::cin >> card;
    c.card = card;
    return c;
}

void
Game::humanPlay(Player &player, const std::vector<Card> &legalPlays)
{
    const std::vector<Card> &hand = player.hand();
    bool legal = false;
    while(!legal)
    {
        Command c = getCommand();
        using namespace Command::Type;
        switch(c.Type)
        {
            case PLAY:
                if(std::find(legalPlays.begin(), legalPlays.end(), c.Card) != legalPlays.end())
                {
                    legal = true;
                    std::cout << "Player " << myCurrentPlayer << " plays " << c.Card << std::endl;
                    p.play(c.Card);
                }
                else
                    std::cout << "This is not a legal play." << std::endl;
                break;
            case DISCARD:
                if(legalPlays.empty())
                {
                    legal = true;
                    std::cout << "Player " << myCurrentPlayer << " discards " << c.Card << std::endl;
                    p.discard(c.Card);
                }
                else
                    std::cout << "You have a legal play. You may not discard." << std::endl;
                break;
            case DECK:
                for(int i = 0; i < 4; i++)
                    printCardList(std::vector<Card>(myDeck.begin() + i*13, myDeck.begin() + (i+1)*13));
                break;
            case QUIT:
                std::cout << "Need to implement exception throw once main is written" << std::endl;
                // throw exception to quit
                break;
            case RAGEQUIT:
                std::cout << "Player " << myCurrentPlayer << " ragequits. A computer will now take over." << std::endl;
                p.ragequit();
                break;
            default:
                std::cout << "!!!!!!!!!uh this shouldnt happen :))!!!!!!!!!" << std::endl;
        }
}

void
Game::constructLegalPlays(const std::vector<Card> &hand, std::vector<Card>& plays)
{
    for (const Card& c : hand)
    {
        if (c == Card(Card::Rank(7), Card::Suit(0)) || c == Card(Card::Rank(7), Card::Suit(1)) ||
            c == Card(Card::Rank(7), Card::Suit(2)) || c == Card(Card::Rank(7), Card::Suit(3)))
            plays.push_back(c);

        for (const std::vector<Card>& v : gameTable)
        {
            if (!v.empty() && v[0].suit().suit() == c.suit().suit())
            {
                Card front = v[0];
                if (front.rank().rank() == c.rank().rank() + 1)
                    plays.push_back(c);
                else
                {
                    Card back = v.back();
                    if (back.rank().rank() == c.rank().rank() - 1)
                        plays.push_back(c);
                }
            }
        }
    }
}

void
Game::startRound()
{
    myDeck = myLastDeck;
    myDeck.shuffle();

    for(std::vector<Card>& list:myTable)
        list.clear();

    for(int i = 0; i < myPlayers.size(); ++i)
    {
        Player& p = myPlayers[i];
        const std::vector<Card>& cards = myDeck.cards(i*13, (i+1)*13);
        for(Card c: cards)
        {
            if(c.suit() == Card::Suit::SPADE && c.rank() == Card::Rank::SEVEN)
                myCurrentPlayer = i;
        }
        p.deal(cards);
    }
}

bool
ame::isGameOver() const
{
    for(Player p: myPlayers)
    {
        if(p.score() >= 80)
            return true;
    }
    return false;
}

bool
Game::isRoundOver() const
{
    for(const Player& p: myPlayers)
    {
        if(p.hand().size())
            return true;
    }
    return false;
}

void
Game::endRound()
{
    for(int i = 0; i < myPlayers.size(); ++i)
    {
        std::cout << "Player " << i << "'s discards:" <<
        int old = p.score();
        const std::vector<Card>&  discarded = p.discarded();
        for(Card c: discarded)
        {
            old -= c.rank().rank();
            std::cout << " " << c;
        }
        std::cout << std::endl;
        std::cout << "Player " << i << "'s score: " << old << " + " << (p.score() - old) << " = " << p.score();
    }
}

void
Game::printWinners() const
{
    for(int i = 0; i < myPlayers.size(); ++i)
    {
        if(p.score() >= 80)
            std::cout << "Player " << i << " wins!" << std::endl;
    }
}

void
Game::printCardList(const std::vector<Card>& list) const
{
    for(Card c: list)
    {
        std::cout << " " << c;
    }
    std::cout << endl;
}
