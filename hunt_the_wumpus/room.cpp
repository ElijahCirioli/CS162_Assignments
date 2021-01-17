#include "event.h"
#include "room.h"
#include <iostream>

/**************************************************
* Function: Default constructor
**************************************************/
Room::Room() {
    event = nullptr;
    contains_rope = false;
}

/**************************************************
* Function: Deconstructor
**************************************************/
Room::~Room() {
    if (event != nullptr)
        delete event;
}

/**************************************************
* Function: Copy constructor
* Inputs: Reference to room to copy
* Outputs: none
**************************************************/
Room::Room(const Room& r) {
    event = r.event;
    contains_rope = r.contains_rope;
}

/**************************************************
* Function: Operator assignment overload
* Inputs: Reference to room to copy
* Outputs: Reference to room
**************************************************/
Room& Room::operator=(const Room& r) {
    if (this != &r) {
        event = r.event;
        contains_rope = r.contains_rope;
    }
    return *this;
}

/**************************************************
* Function: Accessor for event
* Inputs: none
* Outputs: Pointer to event
**************************************************/
Event* Room::get_event() const {
    return event;
}

/**************************************************
* Function: Mutator for event
* Inputs: New event
* Outputs: none
**************************************************/
void Room::set_event(Event* new_event) {
    event = new_event;
}

/**************************************************
* Function: Accessor for whether room contains rope
* Inputs: none
* Outputs: whether room contains rope
**************************************************/
bool Room::get_contains_rope() const {
    return contains_rope;
}

/**************************************************
* Function: Mutator for contains rope
* Inputs: new value for contains rope
* Outputs: none
**************************************************/
void Room::set_contains_rope(bool new_contains_rope) {
    contains_rope = new_contains_rope;
}