#ifndef EVENT_H
#define EVENT_H

#include <string>

using namespace std;

class Event {
private:
public:
    //constructors
    Event(); //default constructor

    //the big three
    virtual ~Event(); //destructor
    Event(const Event&); //copy constructor
    Event& operator=(const Event&); //assignment operator overload

    //other functions
    virtual void percept() const = 0; //warn the player they are close
    virtual int encounter() const = 0; //display message about encounter
    virtual string get_icon() const = 0; //return icon to represent event
};

#endif