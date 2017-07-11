#pragma once

#include <gtkmm.h>

#include "Observer.h"
#include "../game/Card.h"

class Model;
class Controller;
class CardGUI;
class View : public Gtk::Window, public Observer {
    public:
        View (Controller *, Model*, Glib::RefPtr<Gtk::Builder>& builder);
        virtual ~View();
        virtual void update() override;
    
    private:
        Model* myModel;
        Controller* myController;
        CardGUI* myCardGUI;
        Glib::RefPtr<Gtk::Builder> myBuilder;
        Gtk::Image* myTable[4][13] = {{nullptr}};
        Gtk::Button* myPButtons[4] = {nullptr};
        Gtk::Entry* mySeedBox = nullptr;
        bool myIsHumanPlayer[4] = {true};
        
        void updateRound();
        void updateMenu();
        void updatePlayer();
        void updatePlayed();
        void updateHand();

        void startButtonClicked();
        void endGameButtonClicked();
        void rageQuitClicked();
        void playerClicked();
        void cardClicked();

        void showEndRound();
        void showEndGame();

};
