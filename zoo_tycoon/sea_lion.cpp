#include "animal.h"
#include "sea_lion.h"
#include <stdlib.h>
#include <time.h>  

//default constructor
SeaLion::SeaLion() {
    set_num_babies(1);
    set_cost(800);
    set_species("Sea Lion");
}

//returns the revenue this month from the sea lion
int SeaLion::get_revenue(bool high_attendance) const {
    int rev = 0.2 * get_cost();
    if (get_age() < 6)
        rev *= 2;
    if (high_attendance) {
        srand(time(NULL));
        rev += 150;
        rev += rand() % 251;
    }
    return rev;
}

//returns the cost this month from the sea lion
int SeaLion::get_food_cost(int base_cost) const {
    return base_cost;
}

//returns a baby sea lion
Animal* SeaLion::get_baby() const {
    SeaLion* new_sea_lion = new SeaLion;
    return new_sea_lion;
}
