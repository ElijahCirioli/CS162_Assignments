#ifndef CARD_H
#define CARD_H

using namespace std;

class Card {
private:
    int rank; //0-13
    int suit; //0-4
public:
    //constructors
    Card(); //default
    Card(int, int); //suit, rank

    //the big three
    ~Card();
    Card(const Card&);
    Card& operator=(const Card&);

    //accessors and mutators
    int get_suit();
    int get_rank();
    void set_suit(int);
    void set_rank(int);

    //other functions
    void print_card(); //print out suit and rank to iostream
};

#endif