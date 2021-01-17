/******************************************************
** Program: prog.cpp
** Author: Elijah Cirioli
** Date: 11/22/2020
** Description: A pacifist implementation of the classic
**              game Hunt the Wumpus
** Input: 2 command line arguments, cave size and debug mode
** Output: terminal
******************************************************/

#include "event.h"
#include "pit.h"
#include "bats.h"
#include "gold.h"
#include "wumpus.h"
#include "room.h"
#include "player.h"
#include "game.h"
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main(int argc, char** argv) {
    //check if there is enough comments
    if (argc < 3) {
        cout << "Expected 2 arguments, received " << (argc - 1) << endl;
        return 1;
    }
    //check if the size fits within bounds
    int size = atoi(argv[1]);
    if (size < 4 || size > 10) {
        cout << "Size must be between 4 and 10" << endl;
        return 1;
    }
    //check whether to use debug mode
    bool debug = strcmp(argv[2], "true") == 0;

    bool has_played = false; //is this the first game
    int saved_seed; //save random number seed to regenerate map in same way
    while (true) {
        int mode = Game::menu(has_played);
        if (mode == 1) { //play
            saved_seed = time(NULL);
        }
        else if (mode == 2) { //quit
            return 0;
        }
        //create the game and get it started
        Game g(size, debug, saved_seed);
        has_played = true;
        g.draw();
        g.draw_info();
        while (true) {
            if (g.turn())
                break;
        }
    }

    return 0;
}