#include "node.h"

using std::cout;
using std::endl;
using std::left;
using std::setw;

// Price constructor that sets all attributes to zero
Price::Price() {
  this->dollars = 0;
  this->cents = 0;
}

// Price constructor that takes in params dollars and cents
// Sets them to the corresponding attributes
Price::Price(unsigned dollars, unsigned cents) {
  this->dollars = dollars;
  this->cents = cents;
}

// Price deconstructor
Price::~Price() {}

// FoodItem constructor that sets everything that sets all string to empty
// onHand to zero as well
FoodItem::FoodItem() {
  this->id = "";
  this->name = "";
  this->description = "";
  this->price = new Price();
  this->onHand = 0;
}

// FoodItem constructor that sets the params to their corresponding attributes
FoodItem::FoodItem(std::string id, std::string name, std::string description,
                   Price *price, unsigned onHand) {
  this->id = id;
  this->name = name;
  this->description = description;
  this->price = price;
  this->onHand = onHand;
}

// FoodItem deconstructor deletes Price object
FoodItem::~FoodItem() { delete this->price; }

// Prints the details of the item in a specific format
// Used this displaying menu
void FoodItem::printItem() {
  cout << setw(5) << left << this->id << "|";
  cout << setw(NAMELEN) << left << this->name;

  unsigned dollars = this->price->dollars;
  unsigned cents = this->price->cents;

  if (dollars < 10) {
    cout << "|$ " << this->price->dollars << ".";
  } else {
    cout << "|$" << this->price->dollars << ".";
  }

  if (cents < 10) {
    cout << "0" << this->price->cents << endl;
  } else {
    cout << this->price->cents << endl;
  }
}

// Prints the removed output in specific format
void FoodItem::printRemove() {
  cout << "\"" << this->id << " - " << this->name << " - " << this->description
       << "\" " << "has been removed from the system.";
}

// Gets the price of the food item in format "DD.CC" where D is dollars and C is
// cents
std::string FoodItem::getPrice() {
  unsigned dollars = this->price->dollars;
  unsigned cents = this->price->cents;
  std::string price = std::to_string(dollars) + ".";

  if (cents < 10) {
    price += "0" + std::to_string(cents);
  } else {
    price += std::to_string(cents);
  }
  return price;
}

// This is the function that is used to write the details
// of food item in a specific format when saving to a file
std::string FoodItem::writeItem() {
  std::string itemline;
  itemline += this->id + "|";
  itemline += this->name + "|";
  itemline += this->description + "|";

  unsigned dollars = this->price->dollars;
  unsigned cents = this->price->cents;

  itemline += std::to_string(dollars) + ".";

  if (cents < 10) {
    itemline += "0" + std::to_string(cents);
  } else {
    itemline += std::to_string(cents);
  }
  return itemline;
}

// Node constructor
// node will have a pointer to a foodItem
Node::Node() {
  this->foodItem = nullptr;
  this->next = nullptr;
};

// Node constructor that takes a foodItem as a parameter
Node::Node(FoodItem *foodItem) {
  this->foodItem = foodItem;
  this->next = nullptr;
}

// Node deconstructor
Node::~Node() { delete this->foodItem; };
