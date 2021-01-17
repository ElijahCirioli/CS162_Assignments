#include "card.h"
#include "deck.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

//default constructor
Deck::Deck() {
    num_cards = 52;
    for (int s = 0; s < 4; s++)
        for (int r = 0; r < 13; r++)
            cards[s * 13 + r] = Card(s, r);
}

//pass a premade list of cards
Deck::Deck(Card* c) {
    num_cards = 52;
    for (int i = 0; i < num_cards; i++)
        cards[i] = c[i];
}

//destructor
Deck::~Deck() {

}

//copy constructor
Deck::Deck(const Deck& d) {
    num_cards = d.num_cards;
    set_deck(d.cards);
}

//assignment operator overload
Deck& Deck::operator=(const Deck& d) {
    if (this != &d) {
        num_cards = d.num_cards;
        set_deck(d.cards);
    }
    return *this;
}

//returns a card at specified index
Card Deck::get_card(int index) {
    return cards[index];
}

//sets a card at specified index
void Deck::set_card(int index, Card c) {
    cards[index] = c;
}

//returns the number of cards in the deck
int Deck::get_num_cards() {
    return num_cards;
}

//sets the number of cards in the deck
void Deck::set_num_cards(int n) {
    num_cards = n;
}

//returns a list of all the cards
const Card* Deck::get_deck() {
    return cards;
}

//sets the list of all the cards
void Deck::set_deck(const Card* c) {
    for (int i = 0; i < num_cards; i++)
        cards[i] = c[i];
}

//order the cards randomly
void Deck::shuffle() {
    //seed random generator based on time
    srand(time(NULL));
    Card new_deck[num_cards];
    for (int i = 0; i < num_cards; i++) {
        //pick a random card from the original deck until we find one that hasnt been used
        while (true) {
            int rand_index = rand() % 52;
            if (cards[rand_index].get_rank() != -1) {
                new_deck[i] = cards[rand_index];
                cards[rand_index].set_rank(-1);
                break;
            }
        }
    }
    //set old deck the the new one
    set_deck(new_deck);
}

//remove and return the top card from the deck
Card Deck::draw_card() {
    num_cards--;
    return cards[num_cards];
}