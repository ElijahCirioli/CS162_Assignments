#include "card.h"
#include "hand.h"
#include "player.h"
#include <string>
#include <iostream>

//default constructor
Player::Player() {
    name = "";
}

//pass a name
Player::Player(string n) {
    name = n;
}

//destructor
Player::~Player() {
}

//copy constructor
Player::Player(const Player& p) {
    hand = p.hand;
    name = p.name;
}

//assignment operator overload
Player& Player::operator=(const Player& p) {
    if (this != &p) {
        name = p.name;
        hand = p.hand;
    }
    return *this;
}

//return the player's hand
Hand Player::get_hand() {
    return hand;
}

//sets the player's hand
void Player::set_hand(Hand h) {
    hand = h;
}

//return the player's name
string Player::get_name() {
    return name;
}

//sets the player's name
void Player::set_name(string n) {
    name = n;
}

//adds a card to the player's hand, increasing its size
void Player::add_to_hand(Card c) {
    int num_cards = hand.get_num_cards();
    hand.set_num_cards(num_cards + 1);
    Hand new_hand(hand);
    new_hand.set_card(num_cards, c);
    hand = new_hand;
}

//removes a card from the player's hand, decreasing its size
Card Player::remove_from_hand(int index) {
    Card c = hand.get_card(index);
    int num_cards = hand.get_num_cards();
    Hand new_hand(num_cards - 1);

    int offset = 0;
    for (int i = 0; i < num_cards; i++) {
        if (index == i)
            offset = 1;
        else
            new_hand.set_card(i - offset, hand.get_card(i));
    }
    hand = new_hand;
    return c;
}

//ask the player to select a card to play
int Player::prompt_for_card() {
    int selection = 0;
    while (selection <= 0 || selection > hand.get_num_cards()) {
        cout << "SELECT A CARD: ";
        cin >> selection;
        //ensure they entered a number
        if (cin.fail()) {
            cin.clear();
            cin.ignore(256, '\n');
        }
    }
    return selection - 1;
}

//ask the player to choose a suit
int Player::prompt_for_suit() {
    cout << "SUITS: ♠   ♥   ♦   ♣" << endl << "      [1] [2] [3] [4]" << endl;
    int selection = 0;
    while (selection <= 0 || selection > 4) {
        cout << "SELECT A SUIT: ";
        cin >> selection;
        //ensure they entered a number
        if (cin.fail()) {
            cin.clear();
            cin.ignore(256, '\n');
        }
    }
    return selection - 1;
}

//print the player's hand to the iostream, pass whether cards should be shown
void Player::print_hand(bool show_cards) {
    cout << name << ": ";
    for (int i = 0; i < hand.get_num_cards(); i++) {
        if (show_cards) {
            hand.get_card(i).print_card();
            cout << "  ";
        }
        else
            cout << "🂠  ";
    }
    cout << endl;
}