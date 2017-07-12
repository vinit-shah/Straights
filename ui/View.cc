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
            builder->get_widget(ss.str(), myTable[i][j]);
        }
    }

    // Hand Display
    for(int i = 0; i < 13; ++i)
    {
        std::stringstream ss;
        ss << "HC" << i + 1 << "Img";
        CardButton &btn = myCardButtons[i];
        btn.myIndex = i;
        btn.myView = this;
        builder->get_widget(ss.str(), btn.myImage);
        ss.str("");
        ss << "HandCard" << i + 1;
        builder->get_widget(ss.str(), btn.myButton);
        btn.myButton->signal_clicked().connect(sigc::mem_fun(btn, &View::CardButton::clickListener));
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
        ss.str("");
        ss << "P" << (i+1) << "Label2";
        builder->get_widget(ss.str(), playerB.myDiscardLabel);
    }
    reset();
    myModel->subscribe(this);
}

View::~View()
{
    delete myCardGUI;
}

void
View::reset()
{
    char royalty[3] = { 'j', 'q', 'k'};
    
    // Table
    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j  < 13; ++j)
        {
            Glib::RefPtr<Gdk::Pixbuf> pb  = myCardGUI->nothingImage();
            myTable[i][j]->set(pb);
        }
    }

    // Hand Display
    for(int i = 0; i < 13; ++i)
    {
        CardButton &btn = myCardButtons[i];
        btn.myImage->set(myCardGUI->nothingImage());
    }

    // Player Boxes
    for(int i = 0; i < 4; ++i)
    {
        PlayerBlock &playerB = myPlayerBlocks[i];
        playerB.myScoreLabel->set_text("0 points");
        playerB.myDiscardLabel->set_text("0 discards");
    }
}

void
View::PlayerBlock::updateLabel() const
{
    if(myButton->get_label() == "Human")
        myButton->set_label("Computer");
    else
        myButton->set_label("Human");
}

void
View::CardButton::clickListener() const
{
    myView->cardClicked(myIndex);
}

void View::update() {
    //call specific update functions
    if(myModel->isRoundOver())
        updateRound();
    else if(myModel->isGameOver())
        updateGame();
    else
    {
        updateHand();
        updateMenu();
        updatePlayed();
    }
}

void
View::updateGame()
{
    showEndGame();
    reset();
}

void View::updateRound() 
{
    //When round is finished, show scores in a dialog etc..
    showEndRound();
    reset();
    myController->startRound();
}

void View::updateMenu() 
{
    //What buttons are clickable
    int currentPlayer = myModel->getActivePlayer();
    for(int i = 0; i < 4; i++)
    {
        myPlayerBlocks[i].myButton->set_sensitive(i == currentPlayer);
        int lastScore = myModel->getScore(i),
            lastDiscards = myModel->getDiscards(i);
        std::stringstream ss;
        ss << lastScore << " points";
        myPlayerBlocks[i].myScoreLabel->set_text(ss.str());
        ss.str("");
        ss << lastDiscards << " discards";
        myPlayerBlocks[i].myDiscardLabel->set_text(ss.str());
    }
}

void View::updatePlayed()
{
    //get cards that have been played from the model, put them on screen
    const std::vector<std::vector<Card*>> table = myModel->getCardsPlayed();
    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 13; ++j)
        {
            if(table[i][j])
                myTable[i][j]->set(myCardGUI->image(table[i][j]->rank().rank(), table[i][j]->suit().suit()));
        }
    }
}

void View::updateHand() 
{
    //get currentPlayer, show his cards
    const std::vector<Card*> &hand = myModel->getPlayerHand();
    for(int i = 0; i < 13; ++i)
    {
        CardButton &btn = myCardButtons[i]; 
        if(i < hand.size())
            btn.myImage->set(myCardGUI->image(hand[i]->rank().rank(), hand[i]->suit().suit()));
        else
        {
            btn.myImage->set(myCardGUI->nothingImage());
            btn.myButton->set_sensitive(false);
        }
    }
}

void View::basicDialog(const std::string &str)
{
    Gtk::Dialog dial("New Round", *this);
    Gtk::VBox* vbox = dial.get_vbox();
    vbox->pack_start(Gtk::Label(str, true, false));
    dial.add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);
    dial.run();
}

void View::startButtonClicked()
{
    //call to controller's startButtonClicked function
    std::string seed = mySeedBox->get_text();
    std::stringstream ss(seed);
    std::stringstream dialogBoxStr;
    ss << "A new round begins. It's player" << myModel->getActivePlayer() << "'s turn to play.";
    newRoundDialog(dialogBoxStr);
    reset();
    int s;
    ss >> s;
    bool playerTypes[4] = {false};
    for(int i = 0; i < 4; ++i)
    {
        PlayerBlock& pb = myPlayerBlocks[i];
        playerTypes[i] = pb.myButton->get_label() == "Human";
        pb.myButton->set_label("Rage!");
        pb.myButton->signal_clicked().connect(sigc::mem_fun(*this, &View::playerClicked));
    }
    myController->startGame(s, playerTypes);
}

void View::endGameButtonClicked()
{
    //call controller to end game
    myController->endGame();
}

void View::cardClicked(int index)
{
    //call controller to play or discard card
    myController->playCard(index);
}

void View::showEndRound() 
{
    //call controller end round stuff, show dialogue box
    basicDialog(myModel->roundResults());
}

void View::showEndGame()
{
    //call controller to end game
    basicDialog(myModel->gameResults());
}

void View::playerClicked()
{
    myController->ragequit();
}
