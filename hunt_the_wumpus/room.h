#ifndef ROOM_H
#define ROOM_H

#include "event.h"

using namespace std;

class Room {
private:
    Event* event; //pointer to this room's event
    bool contains_rope; //whether this room contains the escape rope
public:
    //constructors
    Room(); //default constructor

    //the big three
    ~Room(); //destructor
    Room(const Room&); //copy constructor
    Room& operator=(const Room&); //assignment operator overload

    //accessors and mutators
    Event* get_event() const;
    void set_event(Event*);
    bool get_contains_rope() const;
    void set_contains_rope(bool);
};


#endif