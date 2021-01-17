#include "card.h"
#include <iostream>

//default constructor
Card::Card() {
    suit = 0;
    rank = 0;
}

//pass suit, rank
Card::Card(int s, int r) {
    suit = s;
    rank = r;
}

//destructor
Card::~Card() {

}

//copy constructor
Card::Card(const Card& c) {
    suit = c.suit;
    rank = c.rank;
}

//assignment operator overload
Card& Card::operator=(const Card& c) {
    if (this != &c) {
        suit = c.suit;
        rank = c.rank;
    }
    return *this;
}

//returns the suit
int Card::get_suit() {
    return suit;
}

//returns the rank 
int Card::get_rank() {
    return rank;
}

//sets the suit
void Card::set_suit(int s) {
    suit = s;
}

//sets the rank
void Card::set_rank(int r) {
    rank = r;
}

//print out suit and rank to iostream
void Card::print_card() {
    const string suits[4] = { "♠", "♥", "♦", "♣" };
    const string ranks[13] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
    cout << ranks[rank] << suits[suit];
}