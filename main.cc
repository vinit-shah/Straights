#include <iostream>
#include <vector>
#include <stdlib.h>

#include "Game.h"

int main(int argc, char* argv[])
{
    Game game;
    if (argc == 2)
        game.startGame(atoi(argv[1]));
    else
        game.startGame(0);
    try
    {
        game.play();
    }
    catch(std::exception & e){}
}
