/******************************************************
** Program: wizard_catalog.cpp
** Author: Elijah Cirioli
** Date: 10/5/2020
** Description: Takes in and catalogs a list of spellbooks
** and allows users to log in and sort by various conditions
** Input: 2 txt files, 1 list of wizards,
** 1 list of spellbooks, provided as arguments
** Output: Possible txt file based on input
******************************************************/

#ifndef WIZARD_CATALOG_H
#define WIZARD_CATALOG_H

#include <string>
#include <fstream>

using namespace std;

struct wizard {
    string name;
    int id;
    string password;
    string position_title;
    float beard_length;
};

struct spellbook {
    string title;
    string author;
    int num_pages;
    int edition;
    int num_spells;
    float avg_success_rate;
    struct spell* s;
};

struct spell {
    string name;
    float success_rate;
    string effect;
};

struct output {
    string name;
    string data;
};

//dynamically allocate an array of spellbooks of the requested size
spellbook* create_spellbooks(int);
//fill spellbook structs with data from spellbooks.txt
void get_spellbook_data(spellbook*, int, ifstream&);
//dynamically allocate an array of spells of the requested size
spell* create_spells(int);
//Fill a spell with data from spellbooks.txt
void get_spell_data(spell*, int, ifstream&);
//dynamically allocate an array of wizards of the requested size
wizard* create_wizards(int);
//fill wizard structs with data from wizards.txt
void get_wizard_data(wizard*, int, ifstream&);
//handle login of user by comparing to wizards file and return index of user
int login(wizard*, int);
//ask how the user wants to sort the list or if they want to quit
void menu(spellbook*, wizard*, int);
//swap the position of two spellbooks
void swap(spellbook*, spellbook*);
//sort spellbooks array based on given function
void bubble_sort(spellbook*, int, bool*);
//return whether there are more pages in book a or b
bool compare_pages(spellbook, spellbook);
//return whether average spell success rate for book a or b is higher
bool compare_success_rate(spellbook, spellbook);
//return whether a user is allowed to look at a given spellbook
bool allowed_access(wizard*, spellbook*);
//sort and return the spellbooks by their number of pages
output* sort_by_num_pages(spellbook*, wizard*, int);
//add spells to the results array based on their effect
void push_by_effect(spellbook*, wizard*, int, string, output**, int*);
//group and return the spells by their effect
output* sort_by_spell_effect(spellbook*, wizard*, int, int);
//sort and return the spellbooks by the average success rate of their spells
output* sort_by_success_rate(spellbook*, wizard*, int);
//write the output array to the terminal
void write_output_to_terminal(output*, string, int);
//write the output array to a file or create the file
void write_output_to_file(output*, string, string, int);
//print results to either terminal or file
void output_results(output*, string, int);
//delete dynamically allocated data
void delete_info(wizard**, int, spellbook**, int);

#endif