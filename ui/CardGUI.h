#pragma once

#include <gdkmm/pixbuf.h>
#include <vector>

class CardGUI 
{
    public:
        CardGUI();
        virtual ~CardGUI();
        
        GLib::RefPtr<Gdk::Pixbuf> image(Rank r, Suit s);
        GLib::RefPtr<Gdk::Pixbuf> nullImage();

    private:
        std::vector < GLib::RefPtr <Gdk::Pixbuf> > deck;
};

