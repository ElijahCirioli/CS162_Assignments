/******************************************************
** Program: prog.cpp
** Author: Elijah Cirioli
** Date: 11/08/2020
** Description: A ripoff of zoo tycoon
** Input: The terminal
** Output: The terminal
******************************************************/

#include "animal.h"
#include "sea_lion.h"
#include "tiger.h"
#include "black_bear.h"
#include "zoo.h"
#include <string>

int main() {
    Zoo z;
    z.print_title();
    z.turn(0, 80, 0);

    return 0;
}