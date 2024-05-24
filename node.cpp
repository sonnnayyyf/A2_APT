#include "node.h"

using std::cout;
using std::endl;
using std::left;
using std::setw;

Price::Price() {
  this->dollars = 0;
  this->cents = 0;
}

Price::Price(unsigned dollars, unsigned cents) {
  this->dollars = dollars;
  this->cents = cents;
}

Price::~Price() {}

FoodItem::FoodItem() {
  this->id = "";
  this->name = "";
  this->description = "";
  this->price = new Price();
  this->onHand = 0;
}

FoodItem::FoodItem(std::string id, std::string name, std::string description,
                   Price *price, unsigned onHand) {
  this->id = id;
  this->name = name;
  this->description = description;
  this->price = price;
  this->onHand = onHand;
}

FoodItem::~FoodItem() { delete this->price; }

void FoodItem::printItem() {
  cout << setw(5) << left << this->id << "|";
  cout << setw(NAMELEN) << left << this->name;

  // For Debugging purposes
  // cout << this->description << "|";

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

void FoodItem::printRemove() {
  cout << "\"" << this->id << " - " << this->name << " - " << this->description
       << "\" " << "has been removed from the system.";
}

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

std::string FoodItem::writeItem() {
  std::string itemline;
  itemline += this->id + "|";
  itemline += this->name + "|";
  itemline += this->description + "|";

  // For Debugging purposes
  // cout << this->description << "|";

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

Node::Node() {
  this->foodItem = nullptr;
  this->next = nullptr;
};

Node::Node(FoodItem *foodItem) {
  this->foodItem = foodItem;
  this->next = nullptr;
}
Node::~Node() { delete this->foodItem; };
