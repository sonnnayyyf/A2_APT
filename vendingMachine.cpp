#include "vendingMachine.h"
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::left;
using std::setw;
using std::string;
using std::vector;

// Constructor
VendingMachine::VendingMachine(LinkedList *foods, Bank *bank, FileLoader loader)
{
    this->foods = foods;
    this->bank = bank;
    this->loader = loader;
}

// Deconstructor
VendingMachine::~VendingMachine()
{
    delete this->bank;
    delete this->foods;
}

bool VendingMachine::loadVendingMachine(string foodFilePath, string coinFilePath)
{
    bool success = false;
    if (this->loader.readFoodData(foodFilePath, this->foods) && this->loader.readCoinData(coinFilePath, this->bank))
    {
        success = true;
    }
    return success;
}

void VendingMachine::addItem()
{
}

bool VendingMachine::removeItem()
{
    bool success = false;
    bool removing = true;
    string input = "";
    cout << "Enter the food id of the food to remove from the menu: ";
    std::getline(cin, input);

    while (removing && !input.empty())
    {
        input.erase(input.find_last_not_of(" \t\r\n\v\f") + 1);
        if (std::cin.eof())
        {
            cout << endl;
            cout << endl;
            cout << "End Of File character inputted" << endl;
            removing = false;
        }
        else
        {
            cout << endl;
            FoodItem *item = this->foods->get(input);
            if (item != nullptr)
            {
                item->printRemove();
                cout << endl;
                this->foods->remove(input);
                success = true;
                removing = false;
            }
            else
            {
                cout << "Item with entered id does not exist. Please try again." << endl;
                cout << "Enter the food id of the food to remove from the menu: ";
                std::getline(cin, input);
            }
        }
    }

    return success;
}

void VendingMachine::purchaseItem()
{
    cout << "Purchase Meal:\n";
    cout << "-------------\n";
    cout << "Please enter the ID of the food you wish to purchase: ";
    string choice = "";
    std::getline(cin, choice);

    if (choice.empty() || cin.eof())
    {
        cout << endl
             << "Purchase cancelled!";
    }
    else
    {
        FoodItem *curr = this->foods->get(choice);
        choice.erase(choice.find_last_not_of(" \t\r\n\v\f") + 1);

        if (curr != nullptr && curr->onHand > 0)
        {
            cout << "You have selected \"" << curr->name << " - " << curr->description << ".\"" << endl;
            cout << "This will cost you $ " << curr->getPrice() << endl;
            cout << "Please hand over the money - type in the value of each note/coin in cents." << endl;
            cout << "Please enter ctrl-D or enter on a new line to cancel this purchase." << endl;

            int dollars = curr->price->dollars;
            int cents = curr->price->cents;

            vector<int> paid_bills = {};
            int toPay = dollars * 100 + cents;
            while (toPay > 0)
            {
                cout << "You still need to give us $ " + std::to_string(toPay / 100) + ".";
                if (toPay % 100 > 9)
                {
                    cout << std::to_string(toPay % 100) + ": ";
                }
                else
                {
                    cout << "0" + std::to_string(toPay % 100) + ": ";
                }

                std::getline(cin, choice);

                if (cin.eof() || choice.empty())
                {
                    cout << endl
                         << "Purchase cancelled!\n";
                    toPay = 0;
                    cancel_purchase(paid_bills);
                }
                else
                {
                    choice.erase(choice.find_last_not_of(" \t\r\n\v\f") + 1);
                    if (Helper::isNumber(choice) == false)
                    {
                        cout << "Error: invalid denomination encountered.\n";
                    }
                    else
                    {
                        int payment = stoi(choice);
                        if (bank->manageBalance(payment, ADD, 1))
                        {
                            paid_bills.push_back(payment);
                            toPay -= payment;
                        }
                    }
                }
            }

            toPay = 0 - toPay;
            if (toPay > 0)
            {
                string changeOutput = "Your change is ";
                if (refund(toPay, 0, changeOutput))
                {
                    cout << changeOutput << endl;
                }
                else
                {
                    cout << "Insufficient change in system. Purchase cancelled.\n";
                    cancel_purchase(paid_bills);
                }
            }
        }
        else
        {
            cout << "The ID is invalid or there is no dish left of the ID\n";
            purchaseItem();
        }
    }
}

void VendingMachine::saveData(string foodFilePath, string coinFilePath)
{
    this->loader.writeCoinData(coinFilePath, this->bank);
    this->loader.writeFoodData(foodFilePath, this->foods);
}

void VendingMachine::displayItems()
{
    this->foods->displayItems();
}

void VendingMachine::displayBalance()
{
    this->bank->displayBalance();
}

void VendingMachine::cancel_purchase(vector<int> paidBills)
{
    for (auto &it : paidBills)
    {
        bank->manageBalance(it, SUBTRACT, 1);
    }
}

bool VendingMachine::refund(unsigned int amount, int index, string &changeOutput)
{
    bool possible = false;

    if (amount == 0)
    {
        possible = true;
    }
    else if (index < NUM_DENOMS)
    {
        int Range = std::min(this->bank->getCoin(index)->getCount(), amount / this->bank->getCoin(index)->getDenom());
        for (int i = Range; i >= 0 && !possible; i--)
        {
            int Remainingamount = amount - (i * this->bank->getCoin(index)->getDenom());
            possible = refund(Remainingamount, index + 1, changeOutput);
            if (possible)
            {
                int return_count = i;
                while (return_count > 0)
                {
                    if (this->bank->getCoin(index)->getDenom() < 100)
                    {
                        int coin = this->bank->getCoin(index)->getDenom();
                        changeOutput += std::to_string(coin) + "c ";
                    }
                    else
                    {
                        int dollar = this->bank->getCoin(index)->getDenom();
                        changeOutput += "$" + std::to_string(dollar / 100);
                        changeOutput += " ";
                    }
                    bank->getCoin(index)->addCount(-1);
                    return_count--;
                }
            }
        }
    }
    return possible;
}