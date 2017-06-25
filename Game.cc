#include <iostream>
#include <string>
#include "Game.h"

Game::Game()
{
    // we only have 4 suits
    myTable.reserve(4);
}

Game::play()
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

void pollNextPlayer()
{
    Player& p = myPlayers[myCurrentPlayer++];
    if( p.type() == Player::Type::Human)
    {
        static const std::string suits[4] = {"Clubs", "Diamonds", "Hearts", "Spades"};
        for(int i = 0; i < 4; ++i)
        {
            std::cout << suits[i];
            printCardList(myTable(i));
        }
        std::cout << "Your hand:";
        const std::vector<Card> &hand = p.hand();
        printCardList(p.hand());
        std::cout << "Legal plays";
        std::vector<Card> &legalPlays;
        constructLegalPlays(hand, legalPlays);
        printCardList(legalPlays);
        
    }
}

Card
getHumanInput()
{
    std::string command, card;
    std::cin >> command;
    if(command == "play")
    {
    }
    else if(command == "discard")
    {
    }

}

void constructLegalPlays(const std::vector<Card> &hand, std::vector<Card>& plays)
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

void startRound()
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
            if(c.suit == Card::Suit::SPADE && c.rank() == Card::Rank::SEVEN)
                myCurrentPlayer = i;
        }
        p.deal(cards);
    }
}

bool isGameOver()
{
    for(Player p: myPlayers)
    {
        if(p.score() >= 80)
            return true;
    }
    return false;
}

bool isRoundOver()
{
    for(const Player& p: myPlayers)
    {
        if(p.hand().size())
            return true;
    }
    return false;
}

void endRound()
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

void printWinners()
{
    for(int i = 0; i < myPlayers.size(); ++i)
    {
        if(p.score() >= 80)
            std::cout << "Player " << i << " wins!" << std::endl;
    }
}

void printCardList(const std::vector<Card>& list)
{
    for(Card c: list)
    {
        std::cout << " " << c;
    }
    std::cout << endl;
}
