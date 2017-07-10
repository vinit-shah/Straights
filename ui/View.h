#pragma once

#include <gtkmm.h>

#include "Observer.h"

class Model;
class Controller;

class View : public Gtk::Window; public Observer {
    public:
        View (Controller *, Model*);
        virtual ~View();
        void update();
    
    private:
        Model* model;
        Controller* controller;
}:
