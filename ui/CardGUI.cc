#include <algorithm>
#include <iterator>
#include <string>

#include "CardGUI.h"

const char* image_names[] = {
    //set up club cards
    "img/0_0.png","img/0_1.png","img/0_2.png","img/0_3.png","img/0_4.png","img/0_5.png",
    "img/0_6.png","img/0_7.png","img/0_8.png","img/0_9.png","img/0_j.png","img/0_q.png",
    "img/0_k.png",
    //set up diamond cards
    "img/1_0.png","img/1_1.png","img/1_2.png","img/1_3.png","img/1_4.png","img/1_5.png",
    "img/1_6.png","img/1_7.png","img/1_8.png","img/1_9.png","img/1_j.png","img/1_q.png",
    "img/1_k.png",
    //set up heart cards
    "img/2_0.png","img/2_1.png","img/2_2.png","img/2_3.png","img/2_4.png","img/2_5.png",
    "img/2_6.png","img/2_7.png","img/2_8.png","img/2_9.png","img/2_j.png","img/2_q.png",
    "img/2_k.png",
    //set up spade cards
    "img/3_0.png","img/3_1.png","img/3_2.png","img/3_3.png","img/3_4.png","img/3_5.png",
    "img/3_6.png","img/3_7.png","img/3_8.png","img/3_9.png","img/3_j.png","img/3_q.png",
    "img/3_k.png",
    //set up null card
    "img/nothing.png"
};

Glib::RefPtr<Gdk::Pixbuf> createPixbuf (const std::string& name)
{
    return Gdk::Pixbuf::create_from_file(name);
}

CardGUI::CardGUI()
{
    std::transform(&image_names[0], &image_names[G_N_ELEMENTS(image_names)],std::back_inserter(deck), &createPixbuf);
}

CardGUI::~CardGUI() {};

GLib::RefPtr<Gdk::Pixbuf> image(Rank r, Suit s) 
{
    int index = s.suit()*13 + r.rank();
    return deck[index];
}

GLib::RefPtr<Gdk::PixBuf> nullImage() 
{
    return deck[deck.size()-1];
}
