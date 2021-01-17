#ifndef GAME_H
#define GAME_H

#include "card.h"
#include "deck.h"
#include "player.h"

using namespace std;

class Game {
private:
    Deck deck; //the deck of cards
    Player players[2]; //the two players
    bool is_player_turn; //is it the human player's turn?
    Card top_card; //the top card that's been revealed
    int turn; //the number turn in the game
public:
    //constructor
    Game();

    //the big three
    ~Game();
    Game(const Game&);
    Game& operator=(const Game&);

    //other functions
    void cpu_turn(); //CPU plays card
    void player_turn(); //make the human play cards
    void print_game(); //print the relevant game information to the iostream
    int check_for_win(); //check to see if someone has won
    void game_over(); //tell the user who has won
    bool prompt_for_new_game(); //returns whether the user wants to play again or not
    void increment_turn(); //go to the next turn 
    void switch_turn(); //switch whether it's the human's turn or not
};

#endif