#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>

using namespace std;

class Animal {
private:
    int age; //age in months
    int cost;  //the cost to buy this animal
    int num_babies; //how many babies the animal has at a time
    string species; //the name of the species 
public:
    //constructors
    Animal(); //default constructor

    //the big three
    ~Animal(); //destructor
    Animal(const Animal&); //copy constructor
    Animal& operator=(const Animal&); //assignment operator overload

    //accessors and mutators
    int get_age() const; //returns the age of the animal in months
    void set_age(int); //sets the age of the animal
    int get_cost() const; //returns the monthly cost of this animal
    void set_cost(int); //sets the monthly cost of this animal
    int get_num_babies() const; //returns the number of babies the species has
    void set_num_babies(int); //sets the number of babies a species has
    string get_species() const; //returns the species of the animal
    void set_species(string); //sets the species of the animal

    //other functions
    void increment_age(); //increases the age of animal by one month
    virtual int get_revenue(bool) const = 0; //calculates and returns the revenue this month from the animal
    virtual int get_food_cost(int) const = 0; //calculates returns the cost this month from the animal
    virtual Animal* get_baby() const = 0; //return a baby of the same species as the animal
};

#endif