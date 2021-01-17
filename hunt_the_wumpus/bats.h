#ifndef BATS_H
#define BATS_H

#include "event.h"
#include <string>

using namespace std;

class Bats : public Event {
private:
public:
    //constructors
    Bats(); //default constructor

    virtual ~Bats(); //destructor

    //other functions
    virtual void percept() const; //warn the player that they are close
    virtual int encounter() const; //announce that the player is here
    virtual string get_icon() const; //return an icon for the map
};

#endif