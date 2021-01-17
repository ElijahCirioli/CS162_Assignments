#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <string>

using namespace std;

class Deck {
private:
    Card cards[52]; //the array of cards
    int num_cards; //how many cards in deck
public:
    //constructors
    Deck();
    Deck(Card*); //pass a premade deck

    //the big three
    ~Deck();
    Deck(const Deck&);
    Deck& operator=(const Deck&);

    //accessors and mutators
    Card get_card(int);
    void set_card(int, Card);
    int get_num_cards();
    void set_num_cards(int);
    const Card* get_deck();
    void set_deck(const Card*);

    //other functions
    void shuffle(); //order the cards randomly
    Card draw_card(); //remove and return the top card from the deck
};

#endif