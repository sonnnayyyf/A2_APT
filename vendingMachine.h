#ifndef VENDINGMACHINE_H
#define VENDINGMACHINE_H
#include "linkedList.h"
#include "bank.h"
#include "fileLoader.h"
#include <iostream>

class VendingMachine
{
public:
    VendingMachine(LinkedList *foods, Bank *bank, FileLoader loader); // constructor
    ~VendingMachine(); // deconstructor

    bool loadVendingMachine(std::string foodFilePath, std::string coinFilePath); // initialize data files
    void addItem();// add a new meal
    bool removeItem(); // remove a meal
    void purchaseItem(); // purchase a meal
    void saveData(std::string foodFilePath, std::string coinFilePath); // save the data before exit
    void displayItems(); // print menu
    void displayBalance(); // print all coins in system, their amount and total
    void cancelPurchase(vector<int> paidBills); // return all paid coins to customer
    void cancelRefund(vector<int> refundedBills); // take back all refunded coins
    bool refund(unsigned int Amount, int index, std::string &changeOutput, vector<int> refundedBills); // return the change to customer after purchase a meal

private:
    Bank *bank;
    LinkedList *foods;
    FileLoader loader;
};

#endif // VENDINGMACHINE_H
