#include "animal.h"
#include "tiger.h"

//default constructor
Tiger::Tiger() {
    set_num_babies(3);
    set_cost(15000);
    set_species("Tiger");
}

//returns the revenue this month from the tiger
int Tiger::get_revenue(bool high_attendance) const {
    int rev = 0.1 * get_cost();
    if (get_age() < 6)
        rev *= 2;
    return rev;
}

//returns the cost this month from the tiger
int Tiger::get_food_cost(int base_cost) const {
    return 5 * base_cost;
}

//returns a baby tiger
Animal* Tiger::get_baby() const {
    Tiger* new_tiger = new Tiger;
    return new_tiger;
}
