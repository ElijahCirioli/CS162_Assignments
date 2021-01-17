#include "event.h"
#include "pit.h"
#include <string>
#include <iostream>

/**************************************************
* Function: Default constructor
**************************************************/
Pit::Pit() {

}

/**************************************************
* Function: Destructor
**************************************************/
Pit::~Pit() {

}

/**************************************************
* Function: Perceive the event nearby
* Inputs: none
* Outputs: none
**************************************************/
void Pit::percept() const {
    cout << "● You feel a breeze." << endl;
}

/**************************************************
* Function: Announce an encounter with the event
* Inputs: none
* Outputs: int representing this event
**************************************************/
int Pit::encounter() const {
    cout << "● You trip and fall down a bottomless pit. This might take a while..." << endl;
    return 3;
}

/**************************************************
* Function: Return an icon for the map
* Inputs: none
* Outputs: icon representing this event
**************************************************/
string Pit::get_icon() const {
    return " ●";
}