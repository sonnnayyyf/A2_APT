#ifndef BANK_H
#define BANK_H
#include "coin.h"
#include "helper.h"
#include "node.h"

// This is the enum that stores the index position of where the each
// denomination would be
enum DenomIndex {
  HUNDRED_DOLLAR_INDEX = 0,
  FIFTY_DOLLAR_INDEX = 1,
  TWENTY_DOLLAR_INDEX = 2,
  TEN_DOLLAR_INDEX = 3,
  FIVE_DOLLAR_INDEX = 4,
  TWO_DOLLAR_INDEX = 5,
  ONE_DOLLAR_INDEX = 6,
  FIFTY_CENT_INDEX = 7,
  TWENTY_CENT_INDEX = 8,
  TEN_CENT_INDEX = 9,
  FIVE_CENT_INDEX = 10,
  LAST = 11
};

// This is used to determine if it is adding or subtracting to a coin
enum Operation {
  ADD,
  SUBTRACT,
};

class Bank {
 public:
  Bank();
  ~Bank();

  // Methods for bank
  void calcTotal();
  float getTotal();
  Coin *getCoin(DenomIndex index);
  Coin *getCoin(int index);
  Coin *getCoinByCent(unsigned cents);
  bool manageBalance(unsigned cents, Operation op, int count);
  void displayBalance();

 private:
  //  Array of coins that will store all the coin data for the system
  Coin *safe[NUM_DENOMS];
  float total;
};

#endif  // COIN_H