#ifndef HAND_H
#define HAND_H

#include "card.h"

using namespace std;

class Hand {
private:
    Card* cards; //the list of cards in the hand
    int num_cards; //the number of cards the player is holding
public:
    //constructors
    Hand();
    Hand(int);

    //the big three
    ~Hand();
    Hand(const Hand&);
    Hand& operator=(const Hand&);

    //accessors and mutators
    int get_num_cards();
    void set_num_cards(int);
    Card* get_cards();
    void set_cards(Card*);
    Card get_card(int);
    void set_card(int, Card);

    //other functions
    int contains_suit(int); //does the hand contain a card of a given suit
    int contains_rank(int); //does the hand contain a card of a given rank
};


#endif