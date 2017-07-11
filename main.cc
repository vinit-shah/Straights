#include <iostream>
#include <vector>
#include <stdlib.h>

#include "ui/View.h"
//#include "Game.h"

int main(int argc, char* argv[]) 
{
    auto app = Gtk::Application::create( argc, argv, "Straights UI" );

    // Model model;
    //Controller controller(&model);
    //View view(&controller, &model);
    //return app->run( view );
    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("P2.glade");
   // Gtk::Window *window = nullptr;
    Gtk::Window *game = new View(nullptr, nullptr, builder);
    builder->get_widget("window1", game);
    app->run(*game);
    return 0;

}



