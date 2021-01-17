#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"
#include "hand.h"
#include <string>

using namespace std;

class Player {
private:
    Hand hand; //the hand of cards the player has
    string name; //the name of the player
public:
    //constructors
    Player();
    Player(string);

    //the big three
    ~Player();
    Player(const Player&);
    Player& operator=(const Player&);

    //accessors and mutators
    Hand get_hand();
    void set_hand(Hand);
    string get_name();
    void set_name(string);

    //other functions
    void add_to_hand(Card); //add a card to the player's hand
    Card remove_from_hand(int); //remove and return a card from the player's hand
    int prompt_for_card(); //ask the player to choose a card to play
    int prompt_for_suit(); //ask the player to choose a suit
    void print_hand(bool); //print the contents of the player's hand to the iostream
};

#endif
