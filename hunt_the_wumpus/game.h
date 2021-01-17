#ifndef GAME_H
#define GAME_H

#include "room.h"
#include "player.h"
#include <vector>

using namespace std;

class Game {
private:
    int cave_size; //the side length of the cave of rooms
    bool debug_mode; //whether events should be displayed on the map
    int process_arrow; //whether there is currently an arrow that must be processed
    vector<vector<Room> > cave; //the 2D vector of rooms
    Player p; //the player object
public:
    //constructors
    Game(); //default constructor
    Game(int, bool, int); //size of cave, whether to use debug mode, seed for random generator

    //the big three
    ~Game(); //destructor
    Game(const Game&); //copy constructor
    Game& operator=(const Game&); //assignment operator overload

    //other functions
    bool turn(); //take user input and draw output to console
    void create_rooms(); //creates vector array of rooms of specified size
    void draw(); //draw the map and the player
    bool draw_info(); //print statements about nearby events
    static int menu(bool); //display a title screen menu, bool for whether they've played before
    bool process_encounters(int); //act out the event from the room the player is in
    void process_arrows(); //check if arrow collides with wumpus or misses
    bool input(); //take the player’s input on where to move
    void game_over(); //display a game over message
    void win(); //display a congratulatory message
    Room* get_empty_room(); //returns a room from the cave that does not have an event or the player in it
};

#endif