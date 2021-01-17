#ifndef BLACK_BEAR_H
#define BLACK_BEAR_H

#include "animal.h"

using namespace std;

class BlackBear : public Animal {
public:
    //constructors
    BlackBear(); //default constructor

    //accessors and mutators
    virtual int get_revenue(bool) const; //returns the revenue this month from the black bear
    virtual int get_food_cost(int) const; //returns the cost this month from the black bear
    virtual Animal* get_baby() const; //returns a baby black bear
};

#endif