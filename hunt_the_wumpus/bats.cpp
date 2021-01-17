#include "event.h"
#include "bats.h"
#include <string>
#include <iostream>

/**************************************************
* Function: Default constructor
**************************************************/
Bats::Bats() {

}

/**************************************************
* Function: Destructor
**************************************************/
Bats::~Bats() {

}

/**************************************************
* Function: Perceive the event nearby
* Inputs: none
* Outputs: none
**************************************************/
void Bats::percept() const {
    cout << "🦇 You hear wings flapping." << endl;
}

/**************************************************
* Function: Announce an encounter with the event
* Inputs: none
* Outputs: int representing this event
**************************************************/
int Bats::encounter() const {
    cout << "🦇 An angry bat whisks you away." << endl;
    return 2;
}

/**************************************************
* Function: Return an icon for the map
* Inputs: none
* Outputs: icon representing this event
**************************************************/
string Bats::get_icon() const {
    return "🦇";
}