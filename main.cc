#include <iostream>
#include <vector>

#include "Game.h"

int main()
{
    Game game;
    game.startGame();
    try
    {
        game.play();
    }
    catch(std::exception & e){}
}
