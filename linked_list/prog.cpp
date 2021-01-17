/******************************************************
** Program: prog.cpp
** Author: Elijah Cirioli
** Date: 12/4/2020
** Description: A template implementation of the linked list data type
** Input: Terminal
** Output: Terminal
******************************************************/

#include "node.hpp"
#include "linked_list.hpp"
#include <iostream>

using namespace std;

void signed_version() {
    Linked_List<int> list;

    //enter numbers
    char cont;
    do {
        cout << "Please enter a number: ";
        int input;
        cin >> input;
        list.push_back(input);
        cout << "Add another number? (y or n): ";
        cin >> cont;
    } while (cont == 'y');

    //sort list
    cout << "Sort ascending or descending? (a or d): ";
    char sort_type;
    cin >> sort_type;
    if (sort_type == 'a') {
        list.sort_ascending();
    }
    else if (sort_type == 'd') {
        list.sort_descending();
    }
    else {
        cout << "Response not recognized." << endl;
        return;
    }

    //print
    cout << "Your linked list is: ";
    list.print();
    cout << "Your list contains " << list.get_num_primes() << " prime numbers." << endl;
}

void unsigned_version() {
    Linked_List<unsigned int> list;

    //enter numbers
    char cont;
    do {
        cout << "Please enter a number: ";
        unsigned int input;
        cin >> input;
        list.push_back(input);
        cout << "Add another number? (y or n): ";
        cin >> cont;
    } while (cont == 'y');

    //sort list
    cout << "Sort ascending or descending? (a or d): ";
    char sort_type;
    cin >> sort_type;
    if (sort_type == 'a') {
        list.sort_ascending();
    }
    else if (sort_type == 'd') {
        list.sort_descending();
    }
    else {
        cout << "Response not recognized." << endl;
        return;
    }

    //print
    cout << "Your linked list is: ";
    list.print();
    cout << "Your list contains " << list.get_num_primes() << " prime numbers." << endl;
}

int main() {
    char cont;
    do {
        cout << endl << "Signed or unsigned int? (s or u): ";
        char data_type;
        cin >> data_type;
        if (data_type == 's') {
            signed_version();
        }
        else if (data_type == 'u') {
            unsigned_version();
        }
        else {
            cout << "Response not recognized." << endl;
            return 1;
        }

        cout << "Do you want to do this again? (y or n): ";
        cin >> cont;
    } while (cont == 'y');

    return 0;
}