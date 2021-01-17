#include "event.h"
#include "gold.h"
#include <string>
#include <iostream>

/**************************************************
* Function: Default constructor
**************************************************/
Gold::Gold() {

}

/**************************************************
* Function: Destructor
**************************************************/
Gold::~Gold() {

}

/**************************************************
* Function: Perceive the event nearby
* Inputs: none
* Outputs: none
**************************************************/
void Gold::percept() const {
    cout << "💎 You see a glimmer nearby." << endl;
}

/**************************************************
* Function: Announce an encounter with the event
* Inputs: none
* Outputs: int representing this event
**************************************************/
int Gold::encounter() const {
    cout << "💎 You've found the treasure! Now you must make it out alive." << endl;
    return 1;
}

/**************************************************
* Function: Return an icon for the map
* Inputs: none
* Outputs: icon representing this event
**************************************************/
string Gold::get_icon() const {
    return "💎";
}