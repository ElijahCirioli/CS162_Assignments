#include "card.h"
#include "hand.h"
#include <iostream>

//default constructor
Hand::Hand() {
    num_cards = 0;
    cards = new Card[num_cards];
}

//pass a number of cards
Hand::Hand(int n) {
    num_cards = n;
    cards = new Card[num_cards];
}

//destructor
Hand::~Hand() {
    delete[] cards;
}

//copy constructor
Hand::Hand(const Hand& h) {
    num_cards = h.num_cards;
    cards = new Card[num_cards];
    for (int i = 0; i < num_cards; i++)
        cards[i] = h.cards[i];
}

//assignment operator overload
Hand& Hand::operator=(const Hand& h) {
    if (this != &h) {
        delete[] cards;
        num_cards = h.num_cards;
        cards = new Card[num_cards];
        for (int i = 0; i < num_cards; i++)
            cards[i] = h.cards[i];
    }
    return *this;
}

//returns the number of cards in the user's hand
int Hand::get_num_cards() {
    return num_cards;
}

//sets the number of cards in the user's hand
void Hand::set_num_cards(int n) {
    num_cards = n;
}

//returns all the cards in the hand
Card* Hand::get_cards() {
    return cards;
}

//sets all of the cards in the hand
void Hand::set_cards(Card* c) {
    for (int i = 0; i < num_cards; i++)
        cards[i] = c[i];
}

//returns a card from a specified index
Card Hand::get_card(int index) {
    return cards[index];
}

//sets a card at a specified index
void Hand::set_card(int index, Card c) {
    cards[index] = c;
}

//does the hand contain a card of a given suit
int Hand::contains_suit(int s) {
    for (int i = 0; i < num_cards; i++)
        if (cards[i].get_suit() == s)
            return i;
    return -1;
}

//does the hand contain a card of a given rank
int Hand::contains_rank(int r) {
    for (int i = 0; i < num_cards; i++)
        if (cards[i].get_rank() == r)
            return i;
    return -1;
}