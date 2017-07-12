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
        Gtk::Entry* mySeedBox = nullptr;
        
        struct PlayerBlock
        {
            Gtk::Button *myButton = nullptr;
            Gtk::Label  *myScoreLabel = nullptr,
                        *myDiscardLabel = nullptr;
            void updateLabel() const;
        };

        struct CardButton
        {
            View *myView = nullptr;
            Gtk::Button *myButton = nullptr;
            Gtk::Image *myImage = nullptr;
            int myIndex = -1;
            void clickListener() const;
        };

        PlayerBlock myPlayerBlocks[4];
        CardButton myCardButtons[13];

        void reset();

        void updateRound();
        void updateGame();
        void updateMenu();
        void updatePlayer();
        void updatePlayed();
        void updateHand();

        void startButtonClicked();
        void endGameButtonClicked();
        void rageQuitClicked();
        void playerClicked();
        void cardClicked(int index);

        void showEndRound();
        void showEndGame();

        void basicDialog(const std::string &str);

};
