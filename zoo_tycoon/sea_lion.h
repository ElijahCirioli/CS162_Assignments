#ifndef SEA_LION_H
#define SEA_LION_H

#include "animal.h"

using namespace std;

class SeaLion : public Animal {
public:
    //constructors
    SeaLion(); //default constructor

    //accessors and mutators
    virtual int get_revenue(bool) const; //returns the revenue this month from the sea lion
    virtual int get_food_cost(int) const; //returns the cost this month from the sea lion
    virtual Animal* get_baby() const; //returns a baby sea lion
};

#endif