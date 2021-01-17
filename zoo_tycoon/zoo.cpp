#include "animal.h"
#include "sea_lion.h"
#include "tiger.h"
#include "black_bear.h"
#include "zoo.h"
#include <stdio.h>
#include <iostream> 
#include <string> 
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <cmath> 

//default constructor
Zoo::Zoo() {
    num_animals = 0;
    animals = new Animal * [num_animals];
    balance = 100000;
    time_passed = 0;
}

//destructor
Zoo::~Zoo() {
    delete[] animals;
}

//copy constructor
Zoo::Zoo(const Zoo& z) {
    num_animals = z.num_animals;
    balance = z.balance;
    time_passed = z.time_passed;
    animals = new Animal * [num_animals];
    for (int i = 0; i < num_animals; i++)
        animals[i] = z.animals[i];
}

//assignment operator overload
Zoo& Zoo::operator=(const Zoo& z) {
    if (this != &z) {
        num_animals = z.num_animals;
        balance = z.balance;
        time_passed = z.time_passed;
        animals = new Animal * [num_animals];
        for (int i = 0; i < num_animals; i++)
            animals[i] = z.animals[i];
    }
    return *this;
}

//execute one turn of the game
void Zoo::turn(int food_selection, int base_food_cost, int other_costs) {
    int revenue = 0, food_costs = 0;
    string event;

    //pick a random event
    srand(time(NULL));
    int event_index = rand() % 4; //0 = sick, 1 = birth, 2 = attendance, 3 = none
    if (num_animals == 0)
        event_index = 3;

    //adjust based on which food option was picked
    int food_cost_multiplier = 1;
    if (food_selection == 2) {
        food_cost_multiplier = 2;
        event_index = rand() % 7; //0 = sick, 1 = birth, 2 = attendance, 3 = none, 4 = birth, 5 = attendance, 6 = none
    }
    else if (food_selection == 3) {
        food_cost_multiplier = 0.5;
        event_index = rand() % 5; //0 = sick, 1 = birth, 2 = attendance, 3 = none, 4 = sick
    }

    //accumulate costs and revenues
    for (int i = 0; i < num_animals; i++) {
        animals[i]->increment_age();
        revenue += animals[i]->get_revenue(event_index == 2);
        food_costs += animals[i]->get_food_cost(base_food_cost * food_cost_multiplier);
    }

    //act out event
    if (event_index == 0 || (event_index == 4 && food_selection == 3))
        event = sick_event(other_costs);
    else if (event_index == 1 || (event_index == 4 && food_selection == 2))
        event = birth_event();
    else if (event_index == 2 || event_index == 5)
        event = "a boom in attendance has occurred. Sea Lions generate extra revenue.";
    else if (event_index == 3 || event_index == 6)
        event = "no special event has occurred.";

    //calculate profit and decide how to display it
    int profit = revenue - other_costs - food_costs;
    char profit_sign = '+';
    if (profit < 0)
        profit_sign = '-';
    balance += profit; //add profit to balance

    print_turn(profit_sign, abs(profit), revenue, other_costs + food_costs, event); //print out one turn
    time_passed++; //go forward one month

    //check if the player lost
    if (balance < 0) {
        printf("\nOh no! You're out of money. That's gonna have to be a game over.\n");
        exit(0);
    }

    select_option(num_animals == 0, false, base_food_cost, 0, 0); //let the player pick what to do
}

//adds an animal to the zoo
void Zoo::add_animal(Animal* a) {
    Animal** new_animals = new Animal * [num_animals + 1];
    for (int i = 0; i < num_animals; i++)
        new_animals[i] = animals[i];
    new_animals[num_animals] = a;

    num_animals++;
    delete[] animals;
    animals = new_animals;
}

//removes an animal from the zoo at the given index
void Zoo::remove_animal(int index) {
    Animal** new_animals = new Animal * [num_animals - 1];
    int offset = 0;
    for (int i = 0; i < num_animals; i++) {
        if (i == index)
            offset = 1;
        else
            new_animals[i - offset] = animals[i];
    }

    num_animals--;
    delete[] animals;
    animals = new_animals;
}

//pick a random animal and make them get sick
string Zoo::sick_event(int& costs) {
    //pick the animal
    int sick_index = rand() % num_animals;
    Animal* ptr = animals[sick_index];
    int sick_cost = ptr->get_cost() / 2;

    //make the string about it
    string str = "a ";
    if (ptr->get_age() < 6) {
        sick_cost *= 2;
        str += "baby ";
    }
    str += ptr->get_species();
    str += " has gotten sick. ";

    //check if they have enough funds to heal it
    if (balance >= sick_cost) {
        balance -= sick_cost;
        costs += sick_cost;
        str += "You pay $" + to_string(sick_cost) + " to heal it.";
    }
    else {
        str += "You don't have enough money so it dies.";
        remove_animal(sick_index);
    }

    return str;
}

//pick a random adult animal and make them give birth
string Zoo::birth_event() {
    //check if there is an adult in the zoo
    bool has_adult = false;
    for (int i = 0; i < num_animals; i++) {
        if (animals[i]->get_age() >= 48) {
            has_adult = true;
            break;
        }
    }

    if (has_adult) {
        //pick an animal to give birth
        int birth_index;
        do
            birth_index = rand() % num_animals;
        while (animals[birth_index]->get_age() < 48);

        Animal* ptr = animals[birth_index];
        for (int i = 0; i < ptr->get_num_babies(); i++)
            add_animal(ptr->get_baby());
        return "a " + ptr->get_species() + " has given birth to " + to_string(ptr->get_num_babies()) + " babies.";
    }

    return "no special event has occurred.";
}

//displays relevant information about this turn to the player
void Zoo::print_turn(char profit_sign, int profit, int revenue, int costs, string event) {
    setlocale(LC_NUMERIC, "");
    printf("\n\n|=======================================================| YEAR %d, MONTH %d \n", time_passed / 12, (time_passed % 12) + 1);
    printf("Balance: $%'d (%c$%'d)\n", balance, profit_sign, profit);
    printf("Revenue: $%'d \n", revenue);
    printf("Costs: $%'d \n\n", costs);
    printf("This month, ");
    cout << event << endl << endl;
    print_animals();
    printf("\nOptions:\n");
    printf("    [1] Buy food\n");
    printf("    [2] Buy animals\n");
    printf("    [3] Next turn\n");
    printf("    [4] Quit\n");
}

//prints all the animals the player has
void Zoo::print_animals() {
    int num_adult_sea_lions = 0, num_baby_sea_lions = 0,
        num_adult_tigers = 0, num_baby_tigers = 0,
        num_adult_black_bears = 0, num_baby_black_bears = 0;

    //count up how many of each species
    for (int i = 0; i < num_animals; i++) {
        Animal* ptr = animals[i];
        if (ptr->get_species() == "Sea Lion") {
            if (ptr->get_age() < 6)
                num_baby_sea_lions++;
            else
                num_adult_sea_lions++;
        }
        else if (ptr->get_species() == "Black Bear") {
            if (ptr->get_age() < 6)
                num_baby_black_bears++;
            else
                num_adult_black_bears++;
        }
        else if (ptr->get_species() == "Tiger") {
            if (ptr->get_age() < 6)
                num_baby_tigers++;
            else
                num_adult_tigers++;
        }
    }

    //print it out
    printf("Sea Lions: %d babies, %d adults\n", num_baby_sea_lions, num_adult_sea_lions);
    printf("Black Bears: %d babies, %d adults\n", num_baby_black_bears, num_adult_black_bears);
    printf("Tigers: %d babies, %d adults\n", num_baby_tigers, num_adult_tigers);
}

//print the title screen
void Zoo::print_title() {
    printf("\n        Elijah Cirioli's\n");
    printf("          𝓦𝓮 𝓫𝓸𝓾𝓰𝓱𝓽 𝓪\n");
    printf("$$$$$$$$\\                     \n");
    printf("\\____$$  |                    \n");
    printf("    $$  /  $$$$$$\\   $$$$$$\\  \n");
    printf("   $$  /  $$  __$$\\ $$  __$$\\ \n");
    printf("  $$  /   $$ /  $$ |$$ /  $$ |\n");
    printf(" $$  /    $$ |  $$ |$$ |  $$ |\n");
    printf("$$$$$$$$\\ \\$$$$$$  |\\$$$$$$  |\n");
    printf("\\________| \\______/  \\______/ \n\n");

    printf("Press enter to begin");
    cin.get();
}

//let the player pick an option for their turn
void Zoo::select_option(bool has_fed, bool has_bought_animal, int base_food_cost, int other_costs, int food_selection) {
    printf("Select an option: ");
    int sel = 0;
    cin >> sel;
    //make sure the input is valid
    if (!cin || sel < 1 || sel > 4) {
        cin.clear();
        cin.ignore(256, '\n');
        select_option(has_fed, has_bought_animal, base_food_cost, other_costs, food_selection);
        return;
    }

    //randomize the food cost unless its the first turn
    int new_food_cost = base_food_cost * (80 + (rand() % 41)) / 100;
    if (time_passed <= 1)
        new_food_cost = base_food_cost;

    //switch for what they chose
    switch (sel) {
    case 1: //Buy food
        printf("\nFood options:\n");
        printf("    [1] Regular: $%'d base cost\n", new_food_cost);
        printf("    [2] Premium: $%'d base cost (0.5x chance of sickness)\n", new_food_cost * 2);
        printf("    [3] Budget: $%'d base cost (2x chance of sickness)\n", new_food_cost / 2);
        food_selection = select_food();
        has_fed = true;
        break;
    case 2: //Buy animals
        if (!has_bought_animal) {
            bool had_no_animals = num_animals == 0;
            printf("\nAnimal options:\n");
            printf("    [1] Sea Lion: $800 each ($160 revenue, 1x food cost)\n");
            printf("    [2] Black Bear: $6,000 each ($600 revenue, 3x food cost)\n");
            printf("    [3] Tiger: $15,000 each ($1,500 revenue, 5x food cost)\n");
            printf("    [4] Back\n");
            other_costs = buy_animals();
            if (other_costs > 0) {
                has_bought_animal = true;
                if (had_no_animals)
                    has_fed = false;
            }
        }
        else
            printf("You have already purchased animals this turn\n");
        break;
    case 3: //Next turn
        if (has_fed)
            turn(food_selection, new_food_cost, other_costs);
        else {
            printf("You must buy food first.\n");
            select_option(has_fed, has_bought_animal, base_food_cost, other_costs, food_selection);
            return;
        }
        break;
    case 4: //Quit
        exit(0);
        break;
    }
    if (sel != 3) {
        printf("\nOptions:\n");
        printf("    [1] Buy food\n");
        printf("    [2] Buy animals\n");
        printf("    [3] Next turn\n");
        printf("    [4] Quit\n");
        select_option(has_fed, has_bought_animal, base_food_cost, other_costs, food_selection);
    }
}

//let the player choose up to two of a single species to buy
int Zoo::buy_animals() {
    printf("Select an option: ");
    int sel = 0, quantity = 0, cost = 0;
    cin >> sel;
    //validate input
    if (!cin || sel < 1 || sel > 4) {
        cin.clear();
        cin.ignore(256, '\n');
        buy_animals();
        return 0;
    }

    //if they dont want to go back
    if (sel != 4) {
        printf("How many to buy (1 or 2): ");
        cin >> quantity;
        //validate input
        if (!cin || quantity < 1 || quantity > 2) {
            cin.clear();
            cin.ignore(256, '\n');
            buy_animals();
            return 0;
        }
        //buy however many the specified of the selected species
        for (int i = 0; i < quantity; i++) {
            Animal* ptr;
            if (sel == 1) {
                SeaLion* s = new SeaLion;
                ptr = s;
            }
            else if (sel == 2) {
                BlackBear* b = new BlackBear;
                ptr = b;
            }
            else if (sel == 3) {
                Tiger* t = new Tiger;
                ptr = t;
            }
            ptr->set_age(48);
            cost += ptr->get_cost();
            add_animal(ptr);
        }
    }
    return cost;
}

//choose which food to buy for the coming turn
int Zoo::select_food() {
    printf("Select an option: ");
    int sel = 0;
    cin >> sel;
    //validate input
    if (!cin || sel < 1 || sel > 3) {
        cin.clear();
        cin.ignore(256, '\n');
        select_food();
        return 0;
    }
    return sel;
}