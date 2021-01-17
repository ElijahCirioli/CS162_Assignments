#include "animal.h"
#include "black_bear.h"

//default constructor
BlackBear::BlackBear() {
    set_num_babies(2);
    set_cost(6000);
    set_species("Black Bear");
}

//returns the revenue this month from the black bear
int BlackBear::get_revenue(bool high_attendance) const {
    int rev = 0.1 * get_cost();
    if (get_age() < 6)
        rev *= 2;
    return rev;
}

//returns the cost this month from the black bear
int BlackBear::get_food_cost(int base_cost) const {
    return 3 * base_cost;
}

//returns a baby black bear
Animal* BlackBear::get_baby() const {
    BlackBear* new_black_bear = new BlackBear;
    return new_black_bear;
}
