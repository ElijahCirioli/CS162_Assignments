#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "node.hpp"
#include <iostream>
#include <cmath>

using namespace std;

/******************************
 *          INTERFACE
 ******************************/
template <class T>
class Linked_List {
private:
    Node<T>* head; // pointer to the first node in the list
    unsigned int length; // the length of the list

    void merge_sort(Node<T>**, unsigned int); // recursively merge sorts the list
    Node<T>* merge_lists(Node<T>*, Node<T>*); // recursibely merges two sorted lists together
    Node<T>* selection_sort(Node<T>**); // recursively performs selection sort on the list
    bool is_prime(T); // returns whether a given number is prime
public:
    Linked_List(); // default constructor
    ~Linked_List(); // destructor
    Linked_List(Linked_List<T>&); // copy constructor
    Linked_List<T>& operator=(Linked_List<T>&); // assignment operator overload
    unsigned int get_length(); // return the length of the list
    void print(); // output a list of all values contained within the list
    void clear(); // delete the entire list (remove all nodes and reset length to 0)
    unsigned int push_front(T); // insert a new value at the front of the list (returns the new length of the list)
    unsigned int push_back(T); // insert a new value at the back of the list (returns the new length of the list)
    unsigned int insert(T, unsigned int); // insert a new value in the list at the specified index (returns the new length of the list)
    T get(unsigned int); // return the value of the node at the specified index
    void set(T, unsigned int); // set the value of the node at the specified index
    void sort_ascending(); // sort the nodes in ascending order. You must implement the recursive Merge Sort algorithm
    void sort_descending(); // sort the nodes in descending order
    unsigned int get_num_primes(); //returns the number of prime numbers in the list
};

/******************************
 *       IMPLEMENTATION
 ******************************/

 //default constructor
template<typename T>
Linked_List<T>::Linked_List() {
    length = 0;
    head = nullptr;
}

//destructor
template<typename T>
Linked_List<T>::~Linked_List() {
    Node<T>* node = head;
    while (node != nullptr) {
        Node<T>* temp = node->get_next();
        delete node;
        node = temp;
    }
}

//copy constructor
template<typename T>
Linked_List<T>::Linked_List(Linked_List<T>& list) {
    head = nullptr;
    length = 0;
    Node<T>* node = list.head;
    while (node != nullptr) {
        push_back(node->get_val());
        node = node->get_next();
    }
}

//assignment operator overload
template<typename T>
Linked_List<T>& Linked_List<T>::operator=(Linked_List<T>& list) {
    if (this != &list) {
        clear();
        Node<T>* node = list.head;
        while (node != nullptr) {
            push_back(node->get_val());
            node = node->get_next();
        }
    }
    return *this;
}

//returns the length of the list
template<typename T>
unsigned int Linked_List<T>::get_length() {
    return length;
}

//prints all the values in the list separated by commas
template<typename T>
void Linked_List<T>::print() {
    Node<T>* node = head;
    while (node != nullptr) {
        cout << node->get_val();
        if (node->get_next() != nullptr)
            cout << ", ";
        node = node->get_next();
    }
    cout << endl;
}

//removes all items from the list
template<typename T>
void Linked_List<T>::clear() {
    Node<T>* node = head;
    while (node != nullptr) {
        Node<T>* temp = node->get_next();
        delete node;
        node = temp;
    }
    length = 0;
    head = nullptr;
}

//pushes a given value to the front of the list
template<typename T>
unsigned int Linked_List<T>::push_front(T val) {
    head = new Node<T>(val, head);
    length++;
    return length;
}

//pushes a given value to the back of the list
template<typename T>
unsigned int Linked_List<T>::push_back(T val) {
    Node<T>* new_node = new Node<T>(val, nullptr);
    if (head == nullptr) {
        head = new_node;
    }
    else {
        Node<T>* node = head;
        while (node->get_next() != nullptr)
            node = node->get_next();
        node->set_next(new_node);
    }
    length++;
    return length;
}

//inserts a given value at a specified index in the list
template<typename T>
unsigned int Linked_List<T>::insert(T val, unsigned int index) {
    if (index == 0)
        return push_front(val);

    Node<T>* node = head;
    for (int i = 0; i < index - 1; i++)
        node = node->get_next();
    node->set_next(new Node<T>(val, node->get_next()));

    length++;
    return length;
}

//returns the value at the specified index
template<typename T>
T Linked_List<T>::get(unsigned int index) {
    Node<T>* node = head;
    for (int i = 0; i < index; i++)
        node = node->get_next();
    return node->get_val();
}

//sets the value at the specified index
template<typename T>
void Linked_List<T>::set(T val, unsigned int index) {
    Node<T>* node = head;
    for (int i = 0; i < index; i++)
        node = node->get_next();
    node->set_val(val);
}

//sorts the list in ascending order through recursive merge sort
template<typename T>
void Linked_List<T>::sort_ascending() {
    merge_sort(&head, length);
}

//recursively sorts a list given a reference to a head pointer and a length
template<typename T>
void Linked_List<T>::merge_sort(Node<T>** head_ptr, unsigned int length) {
    Node<T>* node = *head_ptr;

    //avoid null pointer exception
    if (node->get_next() != nullptr) {
        //split the list in two
        Node<T>* a = node;
        for (int i = 1; i < length / 2; i++)
            node = node->get_next();
        Node<T>* b = node->get_next();
        node->set_next(nullptr);

        //recursively call on both halves
        merge_sort(&a, ceil(length / 2));
        merge_sort(&b, floor(length / 2));

        //merge list back to original
        *head_ptr = merge_lists(a, b);
    }
}

//recursively merges two sorted lists into one sorted list
template<typename T>
Node<T>* Linked_List<T>::merge_lists(Node<T>* a, Node<T>* b) {
    //base cases
    if (a == nullptr)
        return b;
    if (b == nullptr)
        return a;

    //gp with whichever valye is larger and add to result
    Node<T>* result = nullptr;
    if (a->get_val() <= b->get_val()) {
        result = a;
        result->set_next(merge_lists(a->get_next(), b));
    }
    else {
        result = b;
        result->set_next(merge_lists(a, b->get_next()));
    }

    return result;
}

//sorts the list in descending order through recursive selection sort
template<typename T>
void Linked_List<T>::sort_descending() {
    head = selection_sort(&head);
}

//recursively sorts a list in descending order given a reference to the head
template<typename T>
Node<T>* Linked_List<T>::selection_sort(Node<T>** head_ptr) {
    Node<T>* node = *head_ptr;
    //base cases
    if (node == nullptr || node->get_next() == nullptr)
        return node;

    //find the largest value in the list
    Node<T>* max = node;
    unsigned int max_index = 0;
    for (int i = 0; node != nullptr; i++) {
        if (node->get_val() > max->get_val()) {
            max = node;
            max_index = i;
        }
        node = node->get_next();
    }

    //is the max at the front of the list?
    if (max_index == 0) {
        //set the next to the largest after max
        Node<T>* next = max->get_next();
        max->set_next(selection_sort(&next));
    }
    else {
        //find the node before the largest node
        Node<T>* pre_max = *head_ptr;
        for (int i = 0; i < max_index - 1; i++)
            pre_max = pre_max->get_next();

        //move the node to the front and call the function again
        pre_max->set_next(max->get_next());
        max->set_next(selection_sort(head_ptr));
    }

    return max;
}

//returns the number of primes in the list
template<typename T>
unsigned int Linked_List<T>::get_num_primes() {
    unsigned int num_primes = 0;
    Node<T>* node = head;
    while (node != nullptr) {
        if (is_prime(node->get_val()))
            num_primes++;
        node = node->get_next();
    }
    return num_primes;
}

//returns whether a given number is prime
template<typename T>
bool Linked_List<T>::is_prime(T n) {
    if (n <= 1)
        return false;
    for (int i = n - 1; i > 1; i--)
        if (n % i == 0)
            return false;
    return true;
}

#endif