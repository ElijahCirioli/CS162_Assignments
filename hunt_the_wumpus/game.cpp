#include "room.h"
#include "player.h"
#include "game.h"
#include "event.h"
#include "wumpus.h"
#include "gold.h"
#include "pit.h"
#include "bats.h"
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <stdio.h>
#include <unistd.h>

/**************************************************
* Function: Default constructor
**************************************************/
Game::Game() {
    cave_size = 5;
    debug_mode = false;
    process_arrow = 0;
    srand(time(NULL));
    p.set_x(rand() % cave_size);
    p.set_y(rand() % cave_size);
    create_rooms();
}

/**************************************************
* Function: Constructor
* Inputs: size of cave, whether to use debug mode
*         seed for random number generator
* Outputs: none
**************************************************/
Game::Game(int size, bool debug, int seed) {
    cave_size = size;
    debug_mode = debug;
    process_arrow = 0;
    srand(seed);
    p.set_x(rand() % cave_size);
    p.set_y(rand() % cave_size);
    create_rooms();
}

/**************************************************
* Function: Deconstructor
**************************************************/
Game::~Game() {

}

/**************************************************
* Function: Copy constructor
* Inputs: Reference to game object to copy
* Outputs: none
**************************************************/
Game::Game(const Game& g) {
    cave_size = g.cave_size;
    debug_mode = g.debug_mode;
    process_arrow = g.process_arrow;
    p = g.p;
    cave = g.cave;
}

/**************************************************
* Function: Assignment operator overload
* Inputs: Reference to game object to copy
* Outputs: Reference to game object
**************************************************/
Game& Game::operator=(const Game& g) {
    if (this != &g) {
        cave_size = g.cave_size;
        debug_mode = g.debug_mode;
        process_arrow = g.process_arrow;
        p = g.p;
        cave = g.cave;
    }
    return *this;
}

/**************************************************
* Function: Completes one turn of the game
* Inputs: none
* Outputs: none
**************************************************/
bool Game::turn() {
    process_arrow = 0;
    bool exit = input();
    draw();
    bool quit = draw_info();
    return exit || quit;
}

/**************************************************
* Function: Creates the cave of rooms
* Inputs: none
* Outputs: none
**************************************************/
void Game::create_rooms() {
    cave.resize(cave_size);
    for (int y = 0; y < cave_size; y++) {
        cave[y].resize(cave_size);
    }

    cave[p.get_y()][p.get_x()].set_contains_rope(true);

    get_empty_room()->set_event(new Wumpus);
    get_empty_room()->set_event(new Gold);
    get_empty_room()->set_event(new Pit);
    get_empty_room()->set_event(new Pit);
    get_empty_room()->set_event(new Bats);
    get_empty_room()->set_event(new Bats);
}

/**************************************************
* Function: Gets empty room
* Inputs: none
* Outputs: Pointer to an empty room
**************************************************/
Room* Game::get_empty_room() {
    while (true) {
        int x = rand() % cave_size;
        int y = rand() % cave_size;

        if (cave[y][x].get_event() == nullptr && !cave[y][x].get_contains_rope())
            if (p.get_x() != x || p.get_y() != y)
                return &cave[y][x];
    }
}

/**************************************************
* Function: Draws the map and icons
* Inputs: none
* Outputs: none
**************************************************/
void Game::draw() {
    cout << string(50, '\n'); //clear the screen

    //for each row
    for (int y = 0; y < cave_size; y++) {
        //top slice of a row
        for (int x = 0; x < cave_size; x++)
            cout << "#####      ";
        cout << endl;

        //middle slice with icons
        for (int x = 0; x < cave_size; x++) {
            string icon = "  ";
            if (debug_mode && cave[y][x].get_event() != nullptr)
                icon = cave[y][x].get_event()->get_icon();
            if (debug_mode && cave[y][x].get_contains_rope())
                icon = "🚪";
            if (p.get_x() == x && p.get_y() == y)
                icon = "🤠";
            cout << "#" << icon << " #";
            if (x < cave_size - 1)
                cout << "------";
        }
        cout << endl;

        //bottom slice
        for (int x = 0; x < cave_size; x++)
            cout << "#####      ";
        cout << endl;

        if (y < cave_size - 1)
            for (int x = 0; x < cave_size; x++)
                cout << "  |        ";
        cout << endl;
    }
}

/**************************************************
* Function: prints the percepts and encounters
* Inputs: none
* Outputs: none
**************************************************/
bool Game::draw_info() {
    int x = p.get_x();
    int y = p.get_y();
    int num_statements = 0;

    if (x + 1 < cave_size && cave[y][x + 1].get_event() != nullptr) {
        cave[y][x + 1].get_event()->percept();
        num_statements++;
    }
    if (x - 1 >= 0 && cave[y][x - 1].get_event() != nullptr) {
        cave[y][x - 1].get_event()->percept();
        num_statements++;
    }
    if (y + 1 < cave_size && cave[y + 1][x].get_event() != nullptr) {
        cave[y + 1][x].get_event()->percept();
        num_statements++;
    }
    if (y - 1 >= 0 && cave[y - 1][x].get_event() != nullptr) {
        cave[y - 1][x].get_event()->percept();
        num_statements++;
    }

    //if there is an arrow to process
    if (process_arrow != 0) {
        process_arrows();
        num_statements++;
    }

    //execute event where player is standing
    int event = 0;
    if (cave[y][x].get_event() != nullptr) {
        event = cave[y][x].get_event()->encounter();
        num_statements++;
    }

    //fill the rest of the whitespace
    for (int i = num_statements; i < 7; i++)
        cout << endl;

    //test if the player has won
    if (p.get_has_gold() && cave[y][x].get_contains_rope()) {
        cout << "🚪 You've made it to the escape rope!" << endl;
        win();
        return true;
    }

    cout << "[WASD] move    [space] arrow (" << p.get_num_arrows() << ")  [esc] menu" << endl;

    //process encounters and see if the player dies
    if (process_encounters(event))
        return true;

    return false;
}

/**************************************************
* Function: Act out encounters
* Inputs: int to represent the event to enact
* Outputs: none
**************************************************/
bool Game::process_encounters(int event) {
    int x = p.get_x();
    int y = p.get_y();
    switch (event) {
    case 1: //gold
        p.set_has_gold(true);
        delete cave[y][x].get_event();
        cave[y][x].set_event(nullptr);
        break;
    case 2: //bats
        //remove bats
        delete cave[y][x].get_event();
        cave[y][x].set_event(nullptr);

        //teleport player
        x = rand() % cave_size;
        y = rand() % cave_size;
        p.set_x(x);
        p.set_y(y);

        usleep(700000);
        draw();
        draw_info();
        if (cave[y][x].get_event() != nullptr) {
            return process_encounters(cave[y][x].get_event()->encounter());
        }
        break;
    case 3: //pit
        game_over();
        return true;
        break;
    case 4: //wumpus
        game_over();
        return true;
        break;
    }
    return false;
}

/**************************************************
* Function: processes arrows and checks collisions
* Inputs: none
* Outputs: none
**************************************************/
void Game::process_arrows() {
    int x_dir = 0;
    int y_dir = 0;
    switch (process_arrow) {
    case 1: //north
        y_dir = -1;
        break;
    case 2: //east
        x_dir = 1;
        break;
    case 3: //south
        y_dir = 1;
        break;
    case 4: //west
        x_dir = -1;
        break;
    }

    for (int t = 1; t <= 3; t++) {
        int x = p.get_x() + x_dir * t;
        int y = p.get_y() + y_dir * t;

        //if position is in bounds
        if (x >= 0 && y >= 0 && x < cave_size && y < cave_size) {
            //if it hits a wumpus
            if (dynamic_cast<Wumpus*>(cave[y][x].get_event()) != nullptr) {
                delete cave[y][x].get_event();
                cave[y][x].set_event(nullptr);
                cout << "🏹 Your arrow strikes the heart of the Wumpus, killing it." << endl;
                return;
            }
        }
    }

    //move the wumpus
    if (rand() % 4 < 3) { //75% chance
        //find the wumpus
        for (int y = 0; y < cave_size; y++) {
            for (int x = 0; x < cave_size; x++) {
                if (dynamic_cast<Wumpus*>(cave[y][x].get_event()) != nullptr) {
                    get_empty_room()->set_event(new Wumpus);
                    delete cave[y][x].get_event();
                    cave[y][x].set_event(nullptr);
                }
            }
        }
    }

    cout << "🏹 Your arrow harmlessly bounces off a wall." << endl;
}


/**************************************************
* Function: Take user input
* Inputs: none
* Outputs: bool to say whether the user has quit
**************************************************/
bool Game::input() {
    /*
    * I'm aware system is very bad but that's the only way I could figure
    * out how to do the live input in linux without external libraries
    */
    system("stty raw");
    int key = 0;
    bool pressed = false, exit = false;
    do {
        key = getchar();
        switch (key) {
        case 119: //w
            p.move(0, -1, cave_size);
            pressed = true;
            break;
        case 97: //a
            p.move(-1, 0, cave_size);
            pressed = true;
            break;
        case 115: //s
            p.move(0, 1, cave_size);
            pressed = true;
            break;
        case 100: //d
            p.move(1, 0, cave_size);
            pressed = true;
            break;
        case 27: //esc
            pressed = true;
            exit = true;
            break;
        case 32: //space
            process_arrow = p.fire_arrow();
            pressed = true;
            break;
        }
    } while (!pressed);
    system("stty cooked");

    return exit;
}

/**************************************************
* Function: Prints game over message
* Inputs: none
* Outputs: none
**************************************************/
void Game::game_over() {
    cout << endl << "YOU LOSE. PRESS ENTER TO CONTINUE." << endl;
    cin.get();
}

/**************************************************
* Function: Prints congraulatory message
* Inputs: none
* Outputs: none
**************************************************/
void Game::win() {
    cout << endl << "YOU WIN. PRESS ENTER TO CONTINUE." << endl;
    cin.get();
}

/**************************************************
* Function: Draws a menu
* Inputs: bool that represents if this is the
*         first game
* Outputs: int to determine what player wants to do
**************************************************/
int Game::menu(bool has_played_before) {
    cout << string(50, '\n'); //clear the screen
    cout << "                     HUNT    THE" << endl;
    cout << " _     _  __   __  __   __  _______  __   __  _______ " << endl;
    cout << "| | _ | ||  | |  ||  |_|  ||       ||  | |  ||       |" << endl;
    cout << "| || || ||  | |  ||       ||    _  ||  | |  ||  _____|" << endl;
    cout << "|       ||  |_|  ||       ||   |_| ||  |_|  || |_____ " << endl;
    cout << "|       ||       ||       ||    ___||       ||_____  |" << endl;
    cout << "|   _   ||       || ||_|| ||   |    |       | _____| |" << endl;
    cout << "|__| |__||_______||_|   |_||___|    |_______||_______|" << endl;
    cout << endl << "OPTIONS:" << endl;
    cout << "   [1] Play" << endl;
    cout << "   [2] Quit" << endl;
    if (has_played_before)
        cout << "   [3] Replay same map" << endl;
    cout << endl << "SELECT AN OPTION: ";

    int selection;
    do {
        cin >> selection;
    } while (selection < 1 || selection > 3 || (selection == 3 && !has_played_before));
    return selection;
}