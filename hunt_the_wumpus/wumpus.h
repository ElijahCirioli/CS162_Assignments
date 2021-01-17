#ifndef WUMPUS_H
#define WUMPUS_H

#include "event.h"
#include <string>

using namespace std;

class Wumpus : public Event {
private:
public:
    //constructors
    Wumpus(); //default constructor

    virtual ~Wumpus(); //destructor

    //other functions
    virtual void percept() const; //warn the player that they are close
    virtual int encounter() const; //announce that the player is here
    virtual string get_icon() const; //return an icon for the map
};

#endif