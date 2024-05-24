#include "bank.h"

#include <iomanip>
#include <iostream>

using std::cout;
using std::endl;
using std::left;
using std::right;
using std::setw;

// Setting all the coin values with their indexes into the array with count 0
Bank::Bank() {
  this->safe[HUNDRED_DOLLAR_INDEX] = new Coin(HUNDRED_DOLLAR, 0);
  this->safe[FIFTY_DOLLAR_INDEX] = new Coin(FIFTY_DOLLAR, 0);
  this->safe[TWENTY_DOLLAR_INDEX] = new Coin(TWENTY_DOLLAR, 0);
  this->safe[TEN_DOLLAR_INDEX] = new Coin(TEN_DOLLAR, 0);
  this->safe[FIVE_DOLLAR_INDEX] = new Coin(FIVE_DOLLAR, 0);
  this->safe[TWO_DOLLAR_INDEX] = new Coin(TWO_DOLLAR, 0);
  this->safe[ONE_DOLLAR_INDEX] = new Coin(ONE_DOLLAR, 0);
  this->safe[FIFTY_CENT_INDEX] = new Coin(FIFTY_CENT, 0);
  this->safe[TWENTY_CENT_INDEX] = new Coin(TWENTY_CENT, 0);
  this->safe[TEN_CENT_INDEX] = new Coin(TEN_CENT, 0);
  this->safe[FIVE_CENT_INDEX] = new Coin(FIVE_CENT, 0);
  this->total = 0;
}

// Deconstructor goes through all the items in the array and deletes them
Bank::~Bank() {
  for (int i = 0; i < NUM_DENOMS; i++) {
    delete this->safe[i];
  }
}

// Calculates the total of all the coins that exist in the bank and sets it to
// the total attribute
void Bank::calcTotal() {
  this->total = 0;
  for (int i = 0; i < NUM_DENOMS; i++) {
    this->total += this->safe[i]->getTotal();
  }
}

// Returns the total attribute
float Bank::getTotal() { return this->total; }

// Get a coin in the array by DenomIndex
Coin *Bank::getCoin(DenomIndex index) { return this->safe[index]; }

// Get a coin in the array by index
Coin *Bank::getCoin(int index) { return this->safe[index]; }

// Get a coin in the array by DENOM for example 10000 = index 0
Coin *Bank::getCoinByCent(unsigned cents) {
  Coin *coin = nullptr;
  if (cents == HUNDRED_DOLLAR) {
    coin = this->safe[HUNDRED_DOLLAR_INDEX];
  } else if (cents == FIFTY_DOLLAR) {
    coin = this->safe[FIFTY_DOLLAR_INDEX];
  } else if (cents == TWENTY_DOLLAR) {
    coin = this->safe[TWENTY_DOLLAR_INDEX];
  } else if (cents == TEN_DOLLAR) {
    coin = this->safe[TEN_DOLLAR_INDEX];
  } else if (cents == FIVE_DOLLAR) {
    coin = this->safe[FIVE_DOLLAR_INDEX];
  } else if (cents == TWO_DOLLAR) {
    coin = this->safe[TWO_DOLLAR_INDEX];
  } else if (cents == ONE_DOLLAR) {
    coin = this->safe[ONE_DOLLAR_INDEX];
  } else if (cents == FIFTY_CENT) {
    coin = this->safe[FIFTY_CENT_INDEX];
  } else if (cents == TWENTY_CENT) {
    coin = this->safe[TWENTY_CENT_INDEX];
  } else if (cents == TEN_CENT) {
    coin = this->safe[TEN_CENT_INDEX];
  } else if (cents == FIVE_CENT) {
    coin = this->safe[FIVE_CENT_INDEX];
  } else {
    Helper::printInvalidInput("Error: invalid denomination encountered.");
  }
  return coin;
}

// This is for managing balance in the bank
// Operation decides if its adding or subtracting
// Adds or Subtracts specified count into said coin
bool Bank::manageBalance(unsigned cents, Operation op, int count) {
  bool success = false;
  Coin *coin = this->getCoinByCent(cents);

  if (coin != nullptr) {
    if (op == ADD) {
      coin->addCount(count);
      success = true;
    } else if (op == SUBTRACT) {
      coin->minusCount(count);
      success = true;
    }
  }

  this->calcTotal();
  return success;
}

// Displyas all the coins, their counts and their totals in the bank
void Bank::displayBalance() {
  this->calcTotal();
  std::cout << std::fixed << std::setprecision(2);
  cout << "Balance Summary" << endl;
  cout << "-------------" << endl;
  cout << setw(7) << left << "Denom" << "| " << setw(9) << left << "Quantity"
       << "| " << setw(7) << left << "Value" << endl;
  cout << "---------------------------" << endl;

  for (int i = NUM_DENOMS - 1; i >= 0; i--) {
    cout << setw(7) << left << this->safe[i]->getDenom() << "| " << setw(9)
         << left << this->safe[i]->getCount() << "|$" << setw(7) << right
         << this->safe[i]->getTotal() << endl;
  }
  cout << "---------------------------" << endl;
  cout << setw(20) << right << " $" << setw(7) << right << this->total << endl;
}
