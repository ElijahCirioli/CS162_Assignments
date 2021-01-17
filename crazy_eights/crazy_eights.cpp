/******************************************************
** Program: crazy_eights.cpp
** Author: Elijah Cirioli
** Date: 10/25/2020
** Description: A single human vs computer implementation
**              of the card game crazy eights
** Input: Terminal
** Output: Terminal
******************************************************/

#include "card.h"
#include "deck.h"
#include "hand.h"
#include "player.h"
#include "game.h"
#include <iostream>
#include <unistd.h>

int main() {
    while (true) {
        Game game;
        while (true) {
            //player turn
            game.print_game();
            game.player_turn();
            game.print_game();
            if (game.check_for_win() != 0)
                break;

            //intermediate step
            usleep(1000000);
            game.switch_turn();
            game.print_game();
            usleep(1500000);

            //cpu turn
            game.cpu_turn();
            game.print_game();
            if (game.check_for_win() != 0)
                break;

            //go next turn
            usleep(1500000);
            game.increment_turn();
        }
        //game has ended
        game.game_over();
        if (!game.prompt_for_new_game())
            break;
    };
    return 0;
}