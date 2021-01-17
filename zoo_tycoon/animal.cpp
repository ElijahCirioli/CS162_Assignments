#include "animal.h"
#include <string>

//default constructor
Animal::Animal() {
    age = 0;
}

//destructor
Animal::~Animal() {

}

//copy constructor
Animal::Animal(const Animal& a) {
    age = a.age;
    cost = a.cost;
    num_babies = a.num_babies;
    species = a.species;
}

//assignment operator overload
Animal& Animal::operator=(const Animal& a) {
    if (this != &a) {
        age = a.age;
        cost = a.cost;
        num_babies = a.num_babies;
        species = a.species;
    }
    return *this;
}

int Animal::get_age() const {
    return age;
}

void Animal::set_age(int a) {
    age = a;
}

int Animal::get_cost() const {
    return cost;
}

void Animal::set_cost(int c) {
    cost = c;
}

int Animal::get_num_babies() const {
    return num_babies;
}

void Animal::set_num_babies(int n) {
    num_babies = n;
}

string Animal::get_species() const {
    return species;
}

void Animal::set_species(string s) {
    species = s;
}

//increase the age by one
void Animal::increment_age() {
    age++;
}