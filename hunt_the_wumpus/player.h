#ifndef PLAYER_H
#define PLAYER_H

using namespace std;

class Player {
private:
    int x; //the x position in the cave
    int y; //the y position in the cave
    int num_arrows; //the number of arrows remaining
    bool has_gold; //whether the player has found the gold
public:
    //constructors
    Player(); //default constructor
    Player(int, int); //an x and y position to start at

    //accessors and mutators
    int get_x() const;
    void set_x(int);
    int get_y() const;
    void set_y(int);
    int get_num_arrows() const;
    bool get_has_gold() const;
    void set_has_gold(bool);

    //other functions
    void move(int, int, int); //x direction to move, y direction to move, size of cave
    int fire_arrow(); //fires an arrow if the player has any
};

#endif