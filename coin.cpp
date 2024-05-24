#include "coin.h"

// Coin constructor
Coin::Coin(Denomination denom, unsigned count) {
  this->denom = denom;
  this->count = count;
  this->calcTotal();
  this->initialized = false;
}

// Coin deconstructor
// nothing to delete
Coin::~Coin() {}

// Gets the total attribute of the coin
float Coin::getTotal() { return this->total; }

// Gets the denomination attribute of the coin
Denomination Coin::getDenom() { return this->denom; }

// Gets the count attribute of the coin
// Count is how of the denomination we have
unsigned Coin::getCount() { return this->count; }

// Calculates the total of the coin by multiplying denom and count
void Coin::calcTotal() { this->total = this->count * (this->denom / 100.00); }

// Increases the coin's count by param count
void Coin::addCount(int count) {
  this->count += count;
  calcTotal();
}

// Decreases the coin's count by param count
void Coin::minusCount(int count) {
  if (this->count >= (unsigned)count) {
    this->count -= count;
  }
  calcTotal();
}

// Sets initializing attribute to be true
// The initialise attribute is used when loading in coin data from a file
// Every time a new denom is loaded it is initalisesd
// This allows us to avoid duplicates when reading data from coins
//  For example
// 50,3
// 50,6
void Coin::initialize() { this->initialized = true; }

// Gets the initialized attribute of the coin
bool Coin::isInitialized() { return this->initialized; }
