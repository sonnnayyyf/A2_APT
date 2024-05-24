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

// Constructor
LinkedList::LinkedList() {
  head = nullptr;
  tail = nullptr;
  count = 0;
}

// Deconstructor
LinkedList::~LinkedList() {
  Node *curr = this->head;
  Node *prev = nullptr;

  while (curr != nullptr) {
    prev = curr;
    curr = curr->next;
    delete prev;
  }
}

// Returns the number of items in the list
unsigned LinkedList::size() { return count; }

// Returns the food item in the list based on the food id entered
FoodItem *LinkedList::get(string FoodID) {
  FoodItem *retItem = nullptr;

  Node *curr = this->head;
  while (curr != nullptr) {
    if (curr->foodItem->id == FoodID) {
      retItem = curr->foodItem;
    }
    curr = curr->next;
  }
  return retItem;
}

// Adds FoodItem into to linked list and sorts it into position by name on
// insert
void LinkedList::addItem(FoodItem *foodItem) {
  std::string name = foodItem->name;
  Node *newNode = new Node(foodItem);
  newNode->next = nullptr;

  if (tail != nullptr) {
    Node *curr = this->head;
    Node *prev = nullptr;

    // Sorting on insert
    while (curr != nullptr && name > curr->foodItem->name) {
      prev = curr;
      curr = curr->next;
    }

    // Insert the new node
    if (curr == nullptr) {
      // Insert at the end of list
      this->tail->next = newNode;
      this->tail = newNode;
    } else {
      // Insert in the middle of list
      if (prev == nullptr) {
        // Insert at the beginning of list
        newNode->next = this->head;
        this->head = newNode;
      } else {
        prev->next = newNode;
        newNode->next = curr;
      }
    }
  } else {
    // List is empty
    this->head = newNode;
    this->tail = newNode;
  }
  this->count++;
}

// Removes item with entered ID from the list
void LinkedList::remove(std::string foodID) {
  Node *curr = this->head;
  Node *prev = nullptr;
  
  // Traverse the list until we find the node with the given foodID or reach the end of the list
  while (curr->foodItem->id != foodID && curr != nullptr) {
    prev = curr;
    curr = curr->next;
  }

  if (curr != nullptr) {
    if (curr == this->head) {
      removeFront(); // Call the function to remove the head node
    } else if (curr == this->tail) { // If the node to be removed is the tail node
      prev->next = nullptr;
      this->tail = prev;
      delete curr;
    } else { // If the node to be removed is a middle node
      prev->next = curr->next;
      delete curr;
    }
    this->count--;
  }
}

// Removes the first item in the linked list
void LinkedList::removeFront() {
  Node *curr = this->head;
  this->head = curr->next;
  delete curr;
}

// Returns the head of the linked list
Node *LinkedList::getHead() {
  Node *curr = this->head;
  return curr;
}

// Prints menu items
void LinkedList::displayItems() {
  Node *curr = this->head;
  cout << "Food Menu" << endl;
  cout << "---------" << endl;
  cout << setw(5) << left << "ID" << "|" << setw(NAMELEN) << left << "Name"
       << "|" << "Length" << endl;
  cout << "------------------------------------------------------------------"
       << endl;

  while (curr != nullptr) {
    curr->foodItem->printItem();
    curr = curr->next;
  }
  cout << endl;
}

void LinkedList::addFood() {
  string id;
  if (this->count < 9) {
    id = "F000";
  } else {
    id = "F00";
  }

  cout << "The id for the new food will be " << id << this->count + 1 << endl;
  cout << endl;
  cout << "Enter the name of the food: ";
  string name;
  std::getline(cin, name);
  name.erase(name.find_last_not_of(" \t\r\n\v\f") + 1);

  while (name.length() > NAMELEN) {
    cout << "Name is too long, please enter a name with less than " << NAMELEN
         << " characters: ";
    std::getline(cin >> std::ws, name);
    name.erase(name.find_last_not_of(" \t\r\n\v\f") + 1);
  }
  while (name.find("|") != string::npos) {
    cout << "Name cannot contain the character '|', please enter a name "
            "without the character '|': ";
    std::getline(cin >> std::ws, name);
    name.erase(name.find_last_not_of(" \t\r\n\v\f") + 1);
  }

  cout << "Enter the description of the food: ";
  string description;
  std::getline(cin, description);
  description.erase(description.find_last_not_of(" \t\r\n\v\f") + 1);
  while (description.length() > DESCLEN) {
    cout
        << "Description is too long, please enter a description with less than "
        << DESCLEN << " characters: ";
    std::getline(cin >> std::ws, description);
    description.erase(description.find_last_not_of(" \t\r\n\v\f") + 1);
  }
  while (description.find("|") != string::npos) {
    cout << "Description cannot contain the character '|', please enter a "
            "description without the character '|': ";
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
  while (split.size() != 2 || !Helper::isNumber(split[0]) ||
         !Helper::isNumber(split[1])) {
    cout << "Not a valid price, please enter a valid price: ";
    std::getline(cin, dollars);
    dollars.erase(dollars.find_last_not_of(" \t\r\n\v\f") + 1);

    Helper::splitString(dollars, split, ".");
  }
  while (dollars.find("|") != string::npos) {
    cout << "Price cannot contain the character '|', please enter a price "
            "without the character '|': ";
    std::getline(cin >> std::ws, dollars);
    dollars.erase(dollars.find_last_not_of(" \t\r\n\v\f") + 1);
  }
  // create new food item
  id = id + std::to_string(this->count + 1);

  Price *price = new Price(stoi(split[0]), stoi(split[1]));
  FoodItem *item =
      new FoodItem(id, name, description, price, DEFAULT_FOOD_STOCK_LEVEL);

  this->addItem(item);
  cout << "This food \"" << name << " - " << description
       << "\" has now been added to the menu." << endl;
}

int LinkedList::getHighestId() {
  // Find the maximum ID assigned so far
  int maxId = 0;
  for (Node *node = this->head; node != nullptr; node = node->next) {
    int idNum = stoi(node->foodItem->id.substr(3));
    if (idNum > maxId) {
      maxId = idNum;
    }
  }
  return maxId;
}