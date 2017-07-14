#include <iostream>
#include <vector>
#include <stdlib.h>

#include "ui/View.h"
#include "ui/Model.h"
#include "ui/Controller.h"

int main(int argc, char* argv[]) 
{
    auto app = Gtk::Application::create( argc, argv, "straights.ui" );

    Model model;
    Controller controller(&model);
    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("P2.glade");
    Gtk::Window *game = new View(&controller, &model, builder, app);
    builder->get_widget("window1", game);
    app->run(*game);
    return 0;

}



