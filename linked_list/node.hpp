#ifndef NODE_H
#define NODE_H

using namespace std;

/******************************
 *          INTERFACE
 ******************************/
template <class T>
class Node {
private:
    T val; // the value stored in the node
    Node* next; // the pointer to the next node in the list
public:
    Node(); // default constructor
    Node(T, Node<T>*); // constructor
    T get_val(); // returns the value
    void set_val(T); // sets the value
    Node<T>* get_next(); // returns the pointer to the next node
    void set_next(Node<T>*); // sets the pointer to the next node
};

/******************************
 *       IMPLEMENTATION
 ******************************/

 //default constructor
template <typename T>
Node<T>::Node() {
    next = nullptr;
}

//constructor, accepts value and pointer to next
template <typename T>
Node<T>::Node(T v, Node<T>* n) {
    val = v;
    next = n;
}

//returns value
template <typename T>
T Node<T>::get_val() {
    return val;
}

//sets value, accepts new value
template <typename T>
void Node<T>::set_val(T v) {
    val = v;
}

//returns next pointer
template <typename T>
Node<T>* Node<T>::get_next() {
    return next;
}

//sets next pointer, accepts pointer
template <typename T>
void Node<T>::set_next(Node<T>* n) {
    next = n;
}

#endif