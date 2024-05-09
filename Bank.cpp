#include "Bank.h"
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using std::left;
using std::right;
using std::setw;

Bank::Bank()
{
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

Bank::~Bank()
{
    for (int i = 0; i < NUM_DENOMS; i++)
    {
        delete this->safe[i];
    }
    // delete[] this->safe;
}

// // Function for setting Coin object into array
// void Bank::setCoin(DenomIndex index, Coin *coin)
// {
//     this->safe[index] = coin;
//     this->total += coin->getTotal();
// }

// Function for calculating the total of all items in the

void Bank::calcTotal()
{
    this->total = 0;
    for (int i = 0; i < NUM_DENOMS; i++)
    {
        this->total += this->safe[i]->getTotal();
        ;
    }
}

float Bank::getTotal()
{
    return this->total;
}

Coin *Bank::getCoin(DenomIndex index)
{
    return this->safe[index];
}

void Bank::manageBalance(unsigned cents, Operation op, int count)
{
    if (cents == HUNDRED_DOLLAR)
    {
        if (op == ADD)
        {
            this->safe[HUNDRED_DOLLAR_INDEX]->addCount(count);
        }
        else if (op == SUBTRACT)
        {
            this->safe[HUNDRED_DOLLAR_INDEX]->minusCount(count);
        }
    }
    else if (cents == FIFTY_DOLLAR)
    {
        if (op == ADD)
        {
            this->safe[FIFTY_DOLLAR_INDEX]->addCount(count);
        }
        else if (op == SUBTRACT)
        {
            this->safe[FIFTY_DOLLAR_INDEX]->minusCount(count);
        }
    }
    else if (cents == TWENTY_DOLLAR)
    {
        if (op == ADD)
        {
            this->safe[TWENTY_DOLLAR_INDEX]->addCount(count);
        }
        else if (op == SUBTRACT)
        {
            this->safe[TWENTY_DOLLAR_INDEX]->minusCount(count);
        }
    }
    else if (cents == TEN_DOLLAR)
    {
        if (op == ADD)
        {
            this->safe[TEN_DOLLAR_INDEX]->addCount(count);
        }
        else if (op == SUBTRACT)
        {
            this->safe[TEN_DOLLAR_INDEX]->minusCount(count);
        }
    }
    else if (cents == FIVE_DOLLAR)
    {
        if (op == ADD)
        {
            this->safe[FIVE_DOLLAR_INDEX]->addCount(count);
        }
        else if (op == SUBTRACT)
        {
            this->safe[FIVE_DOLLAR_INDEX]->minusCount(count);
        }
    }
    else if (cents == TWO_DOLLAR)
    {
        if (op == ADD)
        {
            this->safe[TWO_DOLLAR_INDEX]->addCount(count);
        }
        else if (op == SUBTRACT)
        {
            this->safe[TWO_DOLLAR_INDEX]->minusCount(count);
        }
    }
    else if (cents == ONE_DOLLAR)
    {
        if (op == ADD)
        {
            this->safe[ONE_DOLLAR_INDEX]->addCount(count);
        }
        else if (op == SUBTRACT)
        {
            this->safe[ONE_DOLLAR_INDEX]->minusCount(count);
        }
    }
    else if (cents == FIFTY_CENT)
    {
        if (op == ADD)
        {
            this->safe[FIFTY_CENT_INDEX]->addCount(count);
        }
        else if (op == SUBTRACT)
        {
            this->safe[FIFTY_CENT_INDEX]->minusCount(count);
        }
    }
    else if (cents == TWENTY_CENT)
    {
        if (op == ADD)
        {
            this->safe[TWENTY_CENT_INDEX]->addCount(count);
        }
        else if (op == SUBTRACT)
        {
            this->safe[TWENTY_CENT_INDEX]->minusCount(count);
        }
    }
    else if (cents == TEN_CENT)
    {
        if (op == ADD)
        {
            this->safe[TEN_CENT_INDEX]->addCount(count);
        }
        else if (op == SUBTRACT)
        {
            this->safe[TEN_CENT_INDEX]->minusCount(count);
        }
    }
    else if (cents == FIVE_CENT)
    {
        if (op == ADD)
        {
            this->safe[FIVE_CENT_INDEX]->addCount(count);
        }
        else if (op == SUBTRACT)
        {
            this->safe[FIVE_CENT_INDEX]->minusCount(count);
        }
    }
    this->calcTotal();
}

void Bank::displayBalance()
{
    std::cout << std::fixed << std::setprecision(2);
    cout << "Balance Summary" << endl;
    cout << "-------------" << endl;
    cout << setw(7) << left << "Denom"
         << "| "
         << setw(9) << left << "Quantity"
         << "| "
         << setw(7) << left << "Value" << endl;
    cout << "---------------------------" << endl;

    for (int i = NUM_DENOMS - 1; i >= 0; i--)
    {
        cout << setw(7) << left << this->safe[i]->getDenom()
             << "| "
             << setw(9) << left << this->safe[i]->getCount()
             << "|$"
             << setw(7) << right << this->safe[i]->getTotal()
             << endl;
    }
    cout << "---------------------------" << endl;
    cout << setw(26) << right << "$ " << this->total << endl;
}