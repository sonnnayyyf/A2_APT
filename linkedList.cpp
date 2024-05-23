#include "linkedList.h"
#include <iostream>
// #include <string>

using std::cin;
using std::cout;
using std::endl;
using std::left;
using std::setw;
using std::string;
using std::vector;

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

Node *LinkedList::getHead()
{
    Node *curr = this->head;
    return curr;
}

bool LinkedList::removeFood()
{
    bool success = false;
    bool removing = true;
    string input = "";
    cout << "Enter the food id of the food to remove from the menu: ";
    std::getline(cin >> std::ws, input);
    input.erase(input.find_last_not_of(" \t\r\n\v\f") + 1);
    while (removing && !input.empty())
    {
        if (std::cin.eof())
        {
            cout << endl;
            cout << endl;
            cout << "End Of File character inputted" << endl;
            removing = false;
        }
        else
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
                std::getline(cin >> std::ws, input);
                input.erase(input.find_last_not_of(" \t\r\n\v\f") + 1);
            }
        }
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

void LinkedList::addFood()
{
    string id;
    if (this->count < 9)
    {
        id = "F000";
    }
    else
    {
        id = "F00";
    }

    cout << "The id for the new food will be " << id << this->count + 1 << endl;
    cout << endl;
    cout << "Enter the name of the food: ";
    string name;
    std::getline(cin, name);
    name.erase(name.find_last_not_of(" \t\r\n\v\f") + 1);

    while (name.length() > NAMELEN)
    {
        cout << "Name is too long, please enter a name with less than " << NAMELEN << " characters: ";
        std::getline(cin >> std::ws, name);
        name.erase(name.find_last_not_of(" \t\r\n\v\f") + 1);
    }
    while (name.find("|") != string::npos)
    {
        cout << "Name cannot contain the character '|', please enter a name without the character '|': ";
        std::getline(cin >> std::ws, name);
        name.erase(name.find_last_not_of(" \t\r\n\v\f") + 1);
    }

    cout << "Enter the description of the food: ";
    string description;
    std::getline(cin, description);
    description.erase(description.find_last_not_of(" \t\r\n\v\f") + 1);
    while (description.length() > DESCLEN)
    {
        cout << "Description is too long, please enter a description with less than " << DESCLEN << " characters: ";
        std::getline(cin >> std::ws, description);
        description.erase(description.find_last_not_of(" \t\r\n\v\f") + 1);
    }
    while (description.find("|") != string::npos)
    {
        cout << "Description cannot contain the character '|', please enter a description without the character '|': ";
        std::getline(cin >> std::ws, description);
        description.erase(description.find_last_not_of(" \t\r\n\v\f") + 1);
    }

    cout << "Enter the price of the food: ";
    string dollars;
    std::getline(cin, dollars);
    dollars.erase(dollars.find_last_not_of(" \t\r\n\v\f") + 1);

    vector<string> split;
    // split the string into dollars and cents
    Helper::splitString(dollars, split, ".");

    // check if the price is valid
    while (split.size() != 2 || !Helper::isNumber(split[0]) || !Helper::isNumber(split[1]))
    {
        cout << "Not a valid price, please enter a valid price: ";
        std::getline(cin, dollars);
        dollars.erase(dollars.find_last_not_of(" \t\r\n\v\f") + 1);

        Helper::splitString(dollars, split, ".");
    }
    while (dollars.find("|") != string::npos)
    {
        cout << "Price cannot contain the character '|', please enter a price without the character '|': ";
        std::getline(cin >> std::ws, dollars);
        dollars.erase(dollars.find_last_not_of(" \t\r\n\v\f") + 1);
    }
    // create new food item
    FoodItem *temp = new FoodItem();
    temp->id = id + std::to_string(this->count + 1);
    temp->name = name;
    temp->description = description;
    temp->price->dollars = stoi(split[0]);
    temp->price->cents = stoi(split[1]);
    this->addBack(temp);
    cout << "This food \"" << name << " - " << description << "\" has now been added to the menu." << endl;
}