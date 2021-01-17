#ifndef PIT_H
#define PIT_H

#include "event.h"
#include <string>

using namespace std;

class Pit : public Event {
private:
public:
    //constructors
    Pit(); //default constructor

    virtual ~Pit(); //destructor

    //other functions
    virtual void percept() const; //warn the player that they are close
    virtual int encounter() const; //announce that the player is here
    virtual string get_icon() const; //return an icon for the map
};

#endif