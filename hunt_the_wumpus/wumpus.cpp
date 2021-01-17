#include "event.h"
#include "wumpus.h"
#include <string>
#include <iostream>

/**************************************************
* Function: Default constructor
**************************************************/
Wumpus::Wumpus() {

}

/**************************************************
* Function: Destructor
**************************************************/
Wumpus::~Wumpus() {

}

/**************************************************
* Function: Perceive the event nearby
* Inputs: none
* Outputs: none
**************************************************/
void Wumpus::percept() const {
    cout << "👾 You smell a terrible stench." << endl;
}

/**************************************************
* Function: Announce an encounter with the event
* Inputs: none
* Outputs: int representing this event
**************************************************/
int Wumpus::encounter() const {
    cout << "👾 You wake the sleeping Wumpus! It devours you in whole." << endl;
    return 4;
}

/**************************************************
* Function: Return an icon for the map
* Inputs: none
* Outputs: icon representing this event
**************************************************/
string Wumpus::get_icon() const {
    return "👾";
}