#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "node.h"
#include <iomanip>

class LinkedList
{
public:
    LinkedList();
    LinkedList(LinkedList &other);
    ~LinkedList();

    // more functions to be added perhaps...
    unsigned size();

    FoodItem *get(std::string FoodItem);

    void addFront(FoodItem *);
    void addBack(FoodItem *);

    void remove(std::string foodID);

    void removeFront();
    void removeBack();

    void printItems();

private:
    // the beginning of the list
    Node *head;
    Node *tail;

    // how many nodes are there in the list?
    unsigned count;
};

#endif // LINKEDLIST_H