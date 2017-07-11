#pragma once

#include <gdkmm/pixbuf.h>
#include <glibmm/refptr.h>
#include <vector>

#include "../Card.h"

class CardGUI 
{
    public:
        CardGUI();
        virtual ~CardGUI();
        
        Glib::RefPtr<Gdk::Pixbuf> image(Card::Rank r, Card::Suit s);
        Glib::RefPtr<Gdk::Pixbuf> nothingImage();

    private:
        std::vector <Glib::RefPtr<Gdk::Pixbuf>> myDeck;
};

