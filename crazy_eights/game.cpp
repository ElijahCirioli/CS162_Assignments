#include "deck.h"
#include "player.h"
#include "game.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>

//default constructor
Game::Game() {
    is_player_turn = true;
    turn = 1;
    deck.shuffle();
    players[0] = Player("YOU");
    players[1] = Player("CPU");
    const int hand_size = 7;
    for (int i = 0; i < hand_size; i++) {
        players[0].add_to_hand(deck.draw_card());
        players[1].add_to_hand(deck.draw_card());
    }
    top_card = deck.draw_card();
}

//destructor
Game::~Game() {

}

//copy constructor
Game::Game(const Game& g) {
    is_player_turn = g.is_player_turn;
    deck = g.deck;
    players[0] = g.players[0];
    players[1] = g.players[1];
    top_card = g.top_card;
    turn = g.turn;
}

//assignment operator overload
Game& Game::operator=(const Game& g) {
    if (this != &g) {
        is_player_turn = g.is_player_turn;
        deck = g.deck;
        players[0] = g.players[0];
        players[1] = g.players[1];
        top_card = g.top_card;
        turn = g.turn;
    }
    return *this;
}

//a human player's turn
void Game::player_turn() {
    Hand player_hand = players[0].get_hand();
    int eight_index = player_hand.contains_rank(7);
    int suit_index = player_hand.contains_suit(top_card.get_suit());
    int rank_index = player_hand.contains_rank(top_card.get_rank());

    //while the player does not have any playable cards
    while (eight_index == -1 && suit_index == -1 && rank_index == -1) {
        cout << "Enter any key to draw a card: ";
        string a;
        cin >> a;
        //add a card to the hand
        players[0].add_to_hand(deck.draw_card());
        print_game();
        //see if there are cards left in the deck
        if (check_for_win() != 0)
            return;
        player_hand = players[0].get_hand();
        eight_index = player_hand.contains_rank(7);
        suit_index = player_hand.contains_suit(top_card.get_suit());
        rank_index = player_hand.contains_rank(top_card.get_rank());
    }

    //prompt to pick a card until they choose a valid one
    while (true) {
        int selection = players[0].prompt_for_card();
        Card card = players[0].get_hand().get_card(selection);
        //if the card is an eight
        if (card.get_rank() == 7) {
            top_card = players[0].remove_from_hand(selection);
            //have the player pick a new suit
            top_card.set_suit(players[0].prompt_for_suit());
            return;
        }
        //if the card has a matching rank
        else if (card.get_rank() == top_card.get_rank()) {
            top_card = players[0].remove_from_hand(selection);
            return;
        }
        //if the card has a matching suit
        else if (card.get_suit() == top_card.get_suit()) {
            top_card = players[0].remove_from_hand(selection);
            return;
        }
    }
}

//have the CPU play automatically
void Game::cpu_turn() {
    while (true) {
        Hand cpu_hand = players[1].get_hand();
        int eight_index = cpu_hand.contains_rank(7);
        int suit_index = cpu_hand.contains_suit(top_card.get_suit());
        int rank_index = cpu_hand.contains_rank(top_card.get_rank());
        //if the computer has an 8
        if (eight_index >= 0) {
            top_card = players[1].remove_from_hand(eight_index);
            //pick a random suit
            srand(time(NULL));
            top_card.set_suit(rand() % 4);
            return;
        }
        //if the computer has a matching suit
        else if (suit_index >= 0) {
            top_card = players[1].remove_from_hand(suit_index);
            return;
        }
        //if the computer has a matching rank
        else if (rank_index >= 0) {
            top_card = players[1].remove_from_hand(rank_index);
            return;
        }
        //if they computer has no usable cards
        else
            players[1].add_to_hand(deck.draw_card());
        if (check_for_win() != 0)
            return;
    }
}

//print the relevant game information to the iostream
void Game::print_game() {
    //print whose turn it is
    if (is_player_turn)
        cout << endl << "=================================== YOUR TURN " << turn << endl << endl;
    else
        cout << endl << "=================================== CPU TURN " << turn << endl << endl;
    //print CPU hand
    players[1].print_hand(false);
    //print deck info
    cout << endl << "TOP: ";
    top_card.print_card();
    cout << "     DECK: 🂠 x " << deck.get_num_cards() << endl << endl;
    //print player hand
    players[0].print_hand(true);

    //print the numbers under the cards
    if (is_player_turn) {
        cout << "   ";
        for (int i = 1; i <= players[0].get_hand().get_num_cards(); i++) {
            if (players[0].get_hand().get_card(i - 1).get_rank() == 9)
                cout << " ";
            if (i < 11)
                cout << " ";
            cout << "[" << i << "]";
        }
    }
    cout << endl;
}

//check to see if someone has won
int Game::check_for_win() {
    int player_num_cards = players[0].get_hand().get_num_cards();
    int cpu_num_cards = players[1].get_hand().get_num_cards();

    //if the deck is gone
    if (deck.get_num_cards() == 0) {
        if (cpu_num_cards > player_num_cards)
            return 1;
        return -1;
    }
    //if the player is out of cards
    if (player_num_cards == 0)
        return 1;
    //if the CPU is out of cards
    if (cpu_num_cards == 0)
        return -1;

    return 0;
}

//go to the next turn 
void Game::increment_turn() {
    turn++;
    switch_turn();
}

//switch whether it's the players's turn or not
void Game::switch_turn() {
    is_player_turn = !is_player_turn;
}

//tell the user who has won
void Game::game_over() {
    cout << endl << "===================================" << endl;
    if (check_for_win() == 1)
        cout << "             YOU WIN" << endl;
    else
        cout << "             CPU WINS" << endl;
    cout << "===================================" << endl;
}

//returns whether the user wants to play again or not
bool Game::prompt_for_new_game() {
    int selection = 0;
    while (selection <= 0 || selection > 2) {
        cout << "[1] PLAY AGAIN      [2] QUIT" << endl;
        cout << "WHAT WOULD YOU LIKE TO DO: ";
        cin >> selection;
        //make sure they entered a number
        if (cin.fail()) {
            cin.clear();
            cin.ignore(256, '\n');
        }
    }
    return selection == 1;
}