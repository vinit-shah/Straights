#pragma once

#include <gtkmm.h>

#include "Observer.h"
#include "../game/Card.h"

class Model;
class Controller;
class CardGUI
class View : public Gtk::Window; public Observer {
    public:
        View (Controller *, Model*);
        virtual ~View();
        virtual void update() override;
    
    private:
        Model* model;
        Controller* controller;
        CardGUI cardGUI;
        Glib::RefPtr<Gtk::Builder> builder;
        
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
