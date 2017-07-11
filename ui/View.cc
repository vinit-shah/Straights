#include <iostream>
#include <string>

#include "CardGUI.h"
#include "Model.h"
#include "Controller.h"
#include "View.h"

View::View(Controller* controller, Model* model, Glib::RefPtr<Gtk::Builder>& builder) : myController(controller) , myModel(model) 
{
    
    Gtk::Button* button;
    builder->get_widget("button1", button);
    button->signal_clicked().connect(sigc::mem_fun(*this, &View::startButtonClicked));

    builder->get_widget("SeedBox", mySeedBox);

    builder->get_widget("button2", button);
    button->signal_clicked().connect(sigc::mem_fun(*this, &View::endGameButtonClicked));

    myCardGUI = new CardGUI();
    char royalty[3] = { 'j', 'q', 'k'};
    
    // Table
    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j  < 13; ++j)
        {
            std::stringstream ss;
            ss << i << "_";
            if(j > 9)
                ss << royalty[j-10];
            else
                ss << j;
            Glib::RefPtr<Gdk::Pixbuf> pb  = myCardGUI->nothingImage();
            builder->get_widget(ss.str(), myTable[i][j]);
            myTable[i][j]->set(pb);
        }
    }

    // Hand Display
    for(int i = 0; i < 13; ++i)
    {
        std::stringstream ss;
        ss << "HC" << i + 1 << "Img";
        Gtk::Image* img;
        Gtk::Button* btn;
        builder->get_widget(ss.str(), img);
        ss.str("");
        ss << "HandCard" << i + 1;
        builder->get_widget(ss.str(), btn);
        img->set(myCardGUI->nothingImage());
        btn->signal_clicked().connect(sigc::mem_fun(*this, &View::cardClicked));
    }

    // Player Boxes
    for(int i = 0; i < 4; ++i)
    {
        PlayerBlock &playerB = myPlayerBlocks[i];
        std::stringstream ss;
        ss << "P" << (i+1) << "Button";
        builder->get_widget(ss.str(), playerB.myButton);
        playerB.myButton->set_label("Human");
        playerB.myButton->signal_clicked().connect(sigc::mem_fun(myPlayerBlocks[i], &View::PlayerBlock::updateLabel));
        ss.str("");
        ss << "P" << (i+1) << "Label1";
        builder->get_widget(ss.str(), playerB.myScoreLabel);
        playerB.myScoreLabel->set_text("0 points");
        ss.str("");
        ss << "P" << (i+1) << "Label2";
        builder->get_widget(ss.str(), playerB.myDiscardLabel);
        playerB.myDiscardLabel->set_text("0 discards");
    }
}

View::~View()
{
    delete myCardGUI;
};

void
View::PlayerBlock::updateLabel() const
{
    std::cout << "updating label" << std::endl;
    if(myButton->get_label() == "Human")
        myButton->set_label("Computer");
    else
        myButton->set_label("Human");
}

void View::update() {
    //call specific update functions
    if(!myModel->isGameActive())
    {

    }
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
    std::string seed = mySeedBox->get_text();
    std::stringstream ss(seed);
    int s;
    ss >> s;
    bool playerTypes[4] = {false};
    for(int i = 0; i < 4; ++i)
    {
        PlayerBlock& pb = myPlayerBlocks[i];
        playerTypes[i] = pb.myButton->get_label() == "Human";
        pb.myButton->signal_clicked().connect(sigc::mem_fun(*this, &View::playerClicked));
    }
    
    myController->startGame(s, playerTypes);
}

void View::endGameButtonClicked()
{
    //call controller to end game
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



