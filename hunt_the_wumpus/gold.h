#ifndef GOLD_H
#define GOLD_H

#include "event.h"
#include <string>

using namespace std;

class Gold : public Event {
private:
public:
    //constructors
    Gold(); //default constructor

    virtual ~Gold(); //destructor

    //other functions
    virtual void percept() const; //warn the player that they are close
    virtual int encounter() const; //announce that the player is here
    virtual string get_icon() const; //return an icon for the map
};

#endif