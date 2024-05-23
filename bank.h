#ifndef BANK_H
#define BANK_H
#include "coin.h"
#include "node.h"
#include "helper.h"

enum DenomIndex
{
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

enum Operation
{
    ADD,
    SUBTRACT,
};

class Bank
{
public:
    Bank();
    ~Bank();

    // void setCoin(DenomIndex denom, Coin *coin);
    void calcTotal();
    float getTotal();
    Coin *getCoin(DenomIndex index);
    Coin *getCoin(int index);
    Coin *getCoinByCent(unsigned cents);
    bool manageBalance(unsigned cents, Operation op, int count);
    void displayBalance();

private:
    Coin *safe[NUM_DENOMS];
    float total;
};

#endif // COIN_H