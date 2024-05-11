#include "linkedList.h"
#include <iostream>
// #include <string>

using std::cout;
using std::endl;
using std::left;
using std::setw;
using std::string;

LinkedList::LinkedList()
{
    head = nullptr;
    tail = nullptr;
    count = 0;
    // TODO
}

LinkedList::LinkedList(LinkedList &other)
{
}

LinkedList::~LinkedList()
{
    Node *curr = this->head;
    Node *prev = nullptr;

    while (curr != nullptr)
    {
        prev = curr;
        curr = curr->next;
        delete prev;
    }
}

unsigned LinkedList::size()
{
    return count;
}

FoodItem *LinkedList::get(std::string FoodID)
{
    FoodItem *retItem = nullptr;

    Node *curr = this->head;
    while (curr != nullptr)
    {
        if (curr->foodItem->id == FoodID)
        {
            retItem = curr->foodItem;
        }
        curr = curr->next;
    }
    return retItem;
}

void LinkedList::addFront(FoodItem *foodItem)
{
    Node *newNode = new Node(foodItem);

    if (this->head == nullptr)
    {
        newNode->next = nullptr;
        this->head = newNode;
        this->tail = newNode;
    }
    else
    {
        newNode->next = this->head;
        this->head = newNode;
    }
    this->count++;
}

void LinkedList::addBack(FoodItem *foodItem)
{
    std::string name = foodItem->name;
    Node *newNode = new Node(foodItem);
    newNode->next = nullptr;

    if (tail != nullptr)
    {
        Node *curr = this->head;
        Node *prev = nullptr;

        // Sorting on insert
        while (curr != nullptr && name > curr->foodItem->name)
        {
            prev = curr;
            curr = curr->next;
        }

        // Insert the new node
        if (curr == nullptr)
        {
            // Insert at the end of list
            this->tail->next = newNode;
            this->tail = newNode;
        }
        else
        {
            // Insert in the middle of list
            if (prev == nullptr)
            {
                // Insert at the beginning of list
                newNode->next = this->head;
                this->head = newNode;
            }
            else
            {
                prev->next = newNode;
                newNode->next = curr;
            }
        }
    }
    else
    {
        // List is empty
        this->head = newNode;
        this->tail = newNode;
    }
    this->count++;
}

void LinkedList::remove(std::string foodID)
{
    Node *curr = this->head;
    Node *prev = nullptr;

    while (curr->foodItem->id != foodID && curr != nullptr)
    {
        prev = curr;
        curr = curr->next;
    }

    if (curr != nullptr)
    {
        if (curr == this->head)
        {
            removeFront();
        }
        else if (curr == this->tail)
        {
            prev->next = nullptr;
            this->tail = prev;
            delete curr;
        }
        else
        {
            prev->next = curr->next;
            delete curr;
        }
        this->count--;
    }
}

void LinkedList::removeFront()
{
    Node *curr = this->head;
    this->head = curr->next;
    delete curr;
}

Node* LinkedList::getHead(){
    Node *curr = this->head;
    return curr;
}

bool LinkedList::removeFood()
{
    bool success = false;
    bool removing = true;
    string input = "";
    cout << "Enter the food id of the food to remove from the menu: ";

    while (removing && std::getline(std::cin, input))
    {
        cout << endl;
        FoodItem *item = this->get(input);
        if (item != nullptr)
        {
            item->printRemove();
            cout << endl;
            this->remove(input);
            success = true;
            removing = false;
        }
        else
        {
            cout << "Item with entered id does not exist. Please try again." << endl;
            cout << "Enter the food id of the food to remove from the menu: ";
        }
    }

    if (std::cin.eof())
    {
        cout << endl;
        cout << endl;
        cout << "End Of File character inputted" << endl;
    }

    return success;
}

// Prints menu items
void LinkedList::printItems()
{
    Node *curr = this->head;
    cout << "Food Menu" << endl;
    cout << "---------" << endl;
    cout << setw(5) << left << "ID"
         << "|"
         << setw(NAMELEN) << left << "Name"
         << "|"
         << "Length" << endl;
    cout << "------------------------------------------------------------------" << endl;

    while (curr != nullptr)
    {
        curr->foodItem->printItem();
        curr = curr->next;
    }
    cout << endl;
}
