#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include "linkedList.h"
#include "bank.h"
#include "string.h"
#include "fileLoader.h"
#include "helper.h"

#define EXPECTED_ARGUMENTS 3

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;

/**
 * manages the running of the program, initialises data structures, loads
 * data, display the main menu, and handles the processing of options.
 * Make sure free memory and close all files before exiting the program..
 **/

void pickMeal(LinkedList *list, Bank *bank);
void purchase(int dollars, int cents, Bank *bank);
// void cancel_purchase(vector<int> paid_list, Bank *bank);
// bool refund(unsigned int Amount, int Index, Bank *bank);
// bool refund_possible(unsigned int Amount, int Index, Bank *bank);
// int min(unsigned int a, unsigned int b);
// bool is_valid_bill(int bill);

bool refundTest(int amount, Bank *bank);

int main(int argc, char **argv)
{
    string mainMenu = "Main Menu:\n";
    mainMenu += "   1. Display Meal Options\n";
    mainMenu += "   2. Purchase Meal\n";
    mainMenu += "   3. Save and Exit\n";
    mainMenu += "Adminstrator-Only Menu:\n";
    mainMenu += "   4. Add Food\n";
    mainMenu += "   5. Remove Food\n";
    mainMenu += "   6. Display Balance\n";
    mainMenu += "   7. Abort Program\n";
    mainMenu += "Select your option (1-7) : ";

    /* validate command line arguments */
    // TODO
    if (argc != EXPECTED_ARGUMENTS)
    {
        Helper::printInvalidInput("Incorrect number of arguments entered.");
    }
    else
    {
        string foodsFile = argv[1];
        string coinsFile = argv[2];

        LinkedList *list = new LinkedList();
        FileLoader fileLoader;
        Bank *bank = new Bank();

        if (fileLoader.loadFoodData(foodsFile, list) && fileLoader.loadCoinData(coinsFile, bank))
        {
            bool menuRunning = true;
            cout << mainMenu;
            string input = "";
            std::getline(cin >> std::ws, input);
            input.erase(input.find_last_not_of(" \t\r\n\v\f") + 1);

            while (menuRunning && !input.empty())
            {
                if (cin.eof())
                {
                    cout << endl;
                    cout << endl;
                    Helper::printInvalidInput("End Of File character inputted.");
                    menuRunning = false;
                }
                else
                {
                    cout << endl;

                    // Validate input 1 to 7
                    // First check if it is a number
                    if (Helper::isNumber(input))
                    {
                        int choice = std::stoi(input);

                        // Now check if number between 1-7
                        if (choice > 0 && choice < 8)
                        {
                            if (choice == 1)
                            {
                                list->printItems();
                            }
                            else if (choice == 2)
                            {
                                pickMeal(list, bank);
                            }
                            else if (choice == 3)
                            {
                                fileLoader.enterFoodData("foodsTest.dat", list);
                                fileLoader.enterCoinData("coinsTest.dat", bank);
                                cout << "Data saved and program exiting." << endl;
                                menuRunning = false;
                            }
                            else if (choice == 4)
                            {
                                // TODO
                                list->addFood();
                            }
                            else if (choice == 5)
                            {
                                // TODO
                                list->removeFood();
                            }
                            else if (choice == 6)
                            {
                                bank->displayBalance();
                            }
                            else if (choice == 7)
                            {
                                cout << "Aborting Program." << endl;
                                exit(EXIT_SUCCESS);
                            }
                        }
                        else
                        {
                            Helper::printInvalidInput("Choice must be between 1-7.");
                        }
                    }
                    else
                    {
                        Helper::printInvalidInput("Choice must be a number between 1-7.");
                    }
                    cout << endl;

                    if (menuRunning != false)
                    {
                        cout << mainMenu;
                        std::getline(cin >> std::ws, input);
                        input.erase(input.find_last_not_of(" \t\r\n\v\f") + 1);
                    }
                }
            }
        }
        else
        {
            Helper::printInvalidInput("Files could not be loaded. Aborting Program.");
        }
        delete list;
        delete bank;
    }

    return EXIT_SUCCESS;
}

// bool is_valid_bill(string bill)
// {
//     bool bill_found = false;
//     string valid_bills[NUM_DENOMS] = {"5", "10", "20", "50", "100", "200", "500", "1000", "2000", "5000", "10000"};
//     for (int i = 0; i < 11; i++)
//     {
//         if (valid_bills[i] == bill)
//         {
//             bill_found = true;
//         }
//     }
//     return bill_found;
// }

// int min(unsigned int a, unsigned int b)
// {
//     if (a > b)
//     {
//         return b;
//     }
//     else
//     {
//         return a;
//     }
// }

// bool refund_possible(unsigned int Amount, int Index, Bank *bank)
// {
//     int valid_bills[NUM_DENOMS] = {10000, 5000, 2000, 1000, 500, 200, 100, 50, 20, 10, 5};
//     if (Amount == 0)
//         return true;
//     if (Index >= NUM_DENOMS)
//         return false;
//     int Range = min(bank->getCoin(Index)->getCount(), Amount / valid_bills[Index]);
//     for (int i = Range; i >= 0; i--)
//     {
//         int RemainingAmount = Amount - (i * valid_bills[Index]);
//         bool result = refund_possible(RemainingAmount, Index + 1, bank);
//         if (result == true)
//         {
//             return true;
//         }
//     }
//     return false;
// }

// bool refund(unsigned int Amount, int Index, Bank *bank)

// {
//     int valid_bills[NUM_DENOMS] = {10000, 5000, 2000, 1000, 500, 200, 100, 50, 20, 10, 5};
//     if (Amount == 0)
//         return true;
//     if (Index >= NUM_DENOMS)
//         return false;
//     int Range = min(bank->getCoin(Index)->getCount(), Amount / valid_bills[Index]);
//     for (int i = Range; i >= 0; i--)
//     {
//         int RemainingAmount = Amount - (i * valid_bills[Index]);
//         if (refund(RemainingAmount, Index + 1, bank))
//         {
//             int return_count = i;
//             while (return_count > 0)
//             {

//                 if (valid_bills[Index] < 100)
//                 {
//                     cout << valid_bills[Index];
//                     cout << "c ";
//                     bank->getCoin(Index)->minusCount(1);
//                 }
//                 else
//                 {
//                     cout << "$";
//                     cout << valid_bills[Index] / 100;
//                     cout << " ";
//                     bank->getCoin(Index)->minusCount(1);
//                 }
//                 return_count--;
//             }
//             return true;
//         }
//     }
//     return false;
// }

// void cancel_purchase(vector<int> paid_list, Bank *bank)
// {
//     for (auto i = paid_list.begin(); i != paid_list.end(); i++)
//     {
//         DenomIndex index;
//         if (*i == FIVE_CENT)
//         {
//             index = FIVE_CENT_INDEX;
//         }
//         else if (*i == TEN_CENT)
//         {
//             index = TEN_CENT_INDEX;
//         }
//         else if (*i == TWENTY_CENT)
//         {
//             index = TWENTY_CENT_INDEX;
//         }
//         else if (*i == FIFTY_CENT)
//         {
//             index = FIFTY_CENT_INDEX;
//         }
//         else if (*i == ONE_DOLLAR)
//         {
//             index = ONE_DOLLAR_INDEX;
//         }
//         else if (*i == TWO_DOLLAR)
//         {
//             index = TWO_DOLLAR_INDEX;
//         }
//         else if (*i == FIVE_DOLLAR)
//         {
//             index = FIVE_DOLLAR_INDEX;
//         }
//         else if (*i == TEN_DOLLAR)
//         {
//             index = TEN_DOLLAR_INDEX;
//         }
//         else if (*i == TWENTY_DOLLAR)
//         {
//             index = TWENTY_DOLLAR_INDEX;
//         }
//         else if (*i == FIFTY_DOLLAR)
//         {
//             index = FIFTY_DOLLAR_INDEX;
//         }
//         else
//         {
//             index = HUNDRED_DOLLAR_INDEX;
//         }
//         bank->getCoin(index)->addCount(-1);
//     }
// }

void purchase(int dollars, int cents, Bank *bank)
{
    vector<int> paidBills = {};
    int toPay = dollars * 100 + cents;

    bool purchasing = true;
    bool revertPurchase = false;

    while (toPay > 0 && purchasing)
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

        string input;
        std::getline(cin, input);
        input.erase(input.find_last_not_of(" \t\r\n\v\f") + 1);

        if (cin.eof() || input.empty())
        {
            cout << ("Purchase cancelled!") << endl;
            revertPurchase = true;
            purchasing = false;
        }
        else
        {
            if (Helper::isNumber(input))
            {
                int payment = std::stoi(input);
                if (bank->manageBalance(payment, ADD, 1))
                {
                    paidBills.push_back(payment);
                    toPay -= payment;
                }
            }
            else
            {
                cout << "Error: invalid denomination encountered." << endl;
            }
        }
    }

    if (revertPurchase == false)
    {
        int leftover = 0 - toPay;
        if (leftover > 0)
        {
            if (refundTest(leftover, bank) == false)
            {
                cout << "Insufficient change in system. Purchase cancelled." << endl;
                for (auto &it : paidBills)
                {
                    bank->manageBalance(it, SUBTRACT, 1);
                }
            }
        }
    }
    else
    {
        for (auto &it : paidBills)
        {
            bank->manageBalance(it, SUBTRACT, 1);
        }
    }
}

void pickMeal(LinkedList *list, Bank *bank)
{
    cout << "Purchase Meal:\n";
    cout << "-------------\n";
    cout << "Please enter the ID of the food you wish to purchase: ";

    string choice = "";
    std::getline(cin >> std::ws, choice);
    choice.erase(choice.find_last_not_of(" \t\r\n\v\f") + 1);
    FoodItem *curr = nullptr;

    if (cin.eof())
    {
        cout << endl
             << "Purchase cancelled!";
    }
    else
    {
        curr = list->get(choice);
        if (curr != nullptr && curr->onHand > 0)
        {
            // foodFound = true;
            cout << "You have selected \"" << curr->name << " - " << curr->description << ".\"" << endl;
            ;
            cout << "This will cost you $ " << std::to_string(curr->price->dollars) << "." << std::to_string(curr->price->cents) << "." << endl;
            ;
            cout << "Please hand over the money - type in the value of each note/coin in cents." << endl;
            cout << "Please enter ctrl-D or enter on a new line to cancel this purchase." << endl;
            purchase(curr->price->dollars, curr->price->cents, bank);
        }
        else
        {
            cout << "The ID is invalid or there is no dish left of the ID" << endl;
            pickMeal(list, bank);
            // print error message
        }
    }
}

bool refundTest(int leftover, Bank *bank)
{
    std::vector<std::pair<Denomination, int>> subtracted;
    bool refunded = false;
    string refundString = "Your change is ";

    for (int i = 0; i < NUM_DENOMS; i++)
    {
        if (leftover > 0)
        {
            Coin *coin = bank->getCoin(i);
            Denomination denom = coin->getDenom();

            int quotient = leftover / denom;

            if (quotient > 0 && coin->getTotal() > 0)
            {
                for (int i = 0; i < quotient; i++)
                {
                    if ((denom % 100) > 0)
                    {
                        refundString += std::to_string(denom);
                        refundString += "c ";
                    }
                    else
                    {
                        refundString += "$";
                        refundString += std::to_string(denom / 100) + " ";
                    }
                }

                leftover -= quotient * denom;
                bank->manageBalance(denom, SUBTRACT, quotient);
                std::pair<Denomination, int> make_pair(denom, quotient);
                subtracted.push_back(make_pair);
            }
        }
    }

    if (leftover == 0)
    {
        refunded = true;
        cout << refundString << endl;
    }
    else
    {
        for (auto &it : subtracted)
        {
            bank->manageBalance(it.first, ADD, it.second);
        }
    }

    return refunded;
}

// Compiling terminal code
// g++ -Wall -Werror -std=c++14 -g -O -o ftt coin.cpp node.cpp linkedList.cpp ftt.cpp bank.cpp helper.cpp fileLoader.cpp
