#ifndef TIGER_H
#define TIGER_H

#include "animal.h"

using namespace std;

class Tiger : public Animal {
public:
    //constructors
    Tiger(); //default constructor

    //accessors and mutators
    virtual int get_revenue(bool) const; //returns the revenue this month from the tiger
    virtual int get_food_cost(int) const; //returns the cost this month from the tiger
    virtual Animal* get_baby() const; //returns a baby tiger
};

#endif