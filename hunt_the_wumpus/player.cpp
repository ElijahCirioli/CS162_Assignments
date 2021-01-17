#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

/**************************************************
* Default constructor
**************************************************/
Player::Player() {
    x = 0;
    y = 0;
    num_arrows = 3;
    has_gold = false;
}

/**************************************************
* Function: Constructor
* Inputs: x position, y position
* Outputs: none
**************************************************/
Player::Player(int x_pos, int y_pos) {
    x = x_pos;
    y = y_pos;
    num_arrows = 3;
    has_gold = false;
}

/**************************************************
* Function: x position accessor
* Inputs: none
* Outputs: x position
**************************************************/
int Player::get_x() const {
    return x;
}

/**************************************************
* Function: x position mutator
* Inputs: new x position
* Outputs: none
**************************************************/
void Player::set_x(int new_x) {
    x = new_x;
}

/**************************************************
* Function: y position accessor
* Inputs: none
* Outputs: y position
**************************************************/
int Player::get_y() const {
    return y;
}

/**************************************************
* Function: y position mutator
* Inputs: new y position
* Outputs: none
**************************************************/
void Player::set_y(int new_y) {
    y = new_y;
}

/**************************************************
* Function: num arrows accessor
* Inputs: none
* Outputs: number of arrows remaining
**************************************************/
int Player::get_num_arrows() const {
    return num_arrows;
}

/**************************************************
* Function: has gold accessor
* Inputs: none
* Outputs: whether the player has the gold
**************************************************/
bool Player::get_has_gold() const {
    return has_gold;
}

/**************************************************
* Function: has gold mutator
* Inputs: whether the player has gold now
* Outputs: none
**************************************************/
void Player::set_has_gold(bool new_has_gold) {
    has_gold = new_has_gold;
}

/**************************************************
* Function: Moves the player if the cave is large enough
* Inputs: x direction to move, y direction to move,
*         size of cave
* Outputs: none
**************************************************/
void Player::move(int x_dir, int y_dir, int cave_size) {
    int new_x = x + x_dir;
    int new_y = y + y_dir;

    if (new_x >= 0 && new_x < cave_size)
        x = new_x;
    if (new_y >= 0 && new_y < cave_size)
        y = new_y;
}

/**************************************************
* Function: Fires an arrow
* Inputs: none
* Outputs: int to indicate which direction arrow was fired
**************************************************/
int Player::fire_arrow() {
    if (num_arrows > 0) {
        num_arrows--;
        cout << "Pick a direction to shoot arrow: ";
        system("stty raw");
        int key = 0;
        bool pressed = false;
        do {
            key = getchar();
            switch (key) {
            case 119: //w
                pressed = true;
                return 1;
                break;
            case 97: //a
                pressed = true;
                return 4;
                break;
            case 115: //s
                pressed = true;
                return 3;
                break;
            case 100: //d
                pressed = true;
                return 2;
                break;
            }
        } while (!pressed);
        system("stty cooked");
    }
    return 0;
}