#ifndef COIN_H
#define COIN_H

// Coin.h defines the coin structure for managing currency in the system.
#define DELIM "," // delimiter

// enumeration representing the various types of currency available in the system.
enum Denomination
{
    HUNDRED_DOLLAR = 10000,
    FIFTY_DOLLAR = 5000,
    TWENTY_DOLLAR = 2000,
    TEN_DOLLAR = 1000,
    FIVE_DOLLAR = 500,
    TWO_DOLLAR = 200,
    ONE_DOLLAR = 100,
    FIFTY_CENT = 50,
    TWENTY_CENT = 20,
    TEN_CENT = 10,
    FIVE_CENT = 5
};

// represents a coin type stored in the cash register perhaps. Each demonination
// will have exactly one of these in the cash register.
class Coin
{
public:
    Coin(Denomination denom, unsigned count);
    ~Coin();

    // Getters
    float getTotal();
    Denomination getDenom();
    unsigned getCount();

    void calcTotal();
    void addCount(int count);
    void minusCount(int count);

private:
    enum Denomination denom;
    float total;
    unsigned count;
};

#endif // COIN_H
