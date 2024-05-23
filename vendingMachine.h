#ifndef VENDINGMACHINE_H
#define VENDINGMACHINE_H
#include "linkedList.h"
#include "bank.h"
#include "fileLoader.h"
#include <iostream>

class VendingMachine
{
public:
    VendingMachine(LinkedList *foods, Bank *bank, FileLoader loader); // Done
    ~VendingMachine();

    bool loadVendingMachine(std::string foodFilePath, std::string coinFilePath);
    void addItem();
    bool removeItem(); // Done
    void purchaseItem();
    void saveData(std::string foodFilePath, std::string coinFilePath); // Done
    void displayItems();                                               // Done
    void displayBalance();
    void cancel_purchase(vector<int> paid_list); // Done
    bool refund(unsigned int Amount, int index, std::string &changeOutput);

private:
    Bank *bank;
    LinkedList *foods;
    FileLoader loader;
};

#endif // VENDINGMACHINE_H