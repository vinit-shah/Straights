#pragma once

#include <vector>
#include <string>

#include "Subject.h"

class Game;

class Model : public Subject 
{
    private:
        Game* myGame;
    
    public:
        Model();

};
