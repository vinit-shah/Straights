#include <iostream>
#include <string>

#include "CardGUI.h"
#include "Model.h"
#include "Controller.h"
#include "View.h"

View::View(Controller* controller, Model* model) : controller(controller) , model(model) 
{
    builder = Gtk::Builder::create_from_file("P2.glade");
    builder->get_widget("window1",this);
}

View::~View() {};

void View::update() {
    //call specific update functions 
}

void View::updateRound() 
{
    //When round is finished, show scores in a dialog etc..
}

void View::updateMenu() 
{
    //What buttons are clickable
}

void View::updatePlayed()
{
    //get cards that have been played from the model, put them on screen
}

void View::updateHand() 
{
    //get currentPlayer, show his cards
}

void View::startButtonClicked()
{
    //call to controller's startButtonClicked function
}

void View::endGameButtonClicked()
{
    //call controller to end game
}

void View::rageQuitClicked()
{
    //call controller to ragequit
}

void View::playerClicked()
{
    //make player human or computer
}

void View::cardClicked()
{
    //call controller to play or discard card
}

void View::showEndRound() 
{
    //call controller end round stuff, show dialogue box
}

void View::showEndGame()
{
    //call controller to end game
}



