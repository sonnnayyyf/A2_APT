#include "Coin.h"

Coin::Coin(Denomination denom, unsigned count)
{
    this->denom = denom;
    this->count = count;
    this->calcTotal();
}

Coin::~Coin()
{
}

float Coin::getTotal()
{
    return this->total;
}

Denomination Coin::getDenom()
{
    return this->denom;
}

unsigned Coin::getCount()
{
    return this->count;
}

void Coin::calcTotal()
{
    this->total = this->count * (this->denom / 100.00);
}

void Coin::addCount(int count)
{
    this->count += count;
    calcTotal();
}

void Coin::minusCount(int count)
{
    if (this->count > (unsigned)count)
    {
        this->count -= count;
    }
    calcTotal();
}
