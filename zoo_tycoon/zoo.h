#ifndef ZOO_H
#define ZOO_H

#include "animal.h"
#include <string>

using namespace std;

class Zoo {
private:
    Animal** animals; //all the animals in the zoo
    int num_animals; //the amount of animals the zoo has
    int balance; //the amount of money the player has
    int time_passed; //the time that has passed (also the turn tracker)
public:
    //constructors
    Zoo(); //default constructor

    //the big three
    ~Zoo(); //destructor
    Zoo(const Zoo&); //copy constructor
    Zoo& operator=(const Zoo&); //assignment operator overload

    //display functions
    void print_turn(char, int, int, int, string); //displays relevant information about this turn to the player
    void print_animals(); //prints all the animals the player has
    void print_title(); //print the title screen

    //other functions
    void turn(int, int, int); //executes one turn of the game
    void add_animal(Animal*); //adds an animal to the zoo
    void remove_animal(int); //removes an animal from the zoo at the given index
    string sick_event(int&); //pick a random animal and make them get sick
    string birth_event(); //pick a random adult animal and make them give birth
    void pay_costs(); //subtract the costs of all animals from the balance
    void collect_revenues(); //add the revenues of all the animals to the balance
    int buy_animals(); //let the player choose up to two of a single species to buy
    void select_option(bool, bool, int, int, int); //let the player pick an option for their turn
    int select_food(); //let the player pick the type of food to feed the animals
};

#endif