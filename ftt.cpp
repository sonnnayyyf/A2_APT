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
void cancel_purchase(vector<int> paid_list, Bank *bank);
bool refund(unsigned int Amount, int Index, Bank *bank);
bool refund_possible(unsigned int Amount, int Index, Bank *bank);
int min(unsigned int a, unsigned int b);
bool is_valid_bill(int bill);

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
                                //this is where purchasing a meal starts. The process will involve the meal list and the coins, either added more or remove for refund
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
// check if the coin is allowed in the denomination accepted list
bool is_valid_bill(string bill)
{
    bool bill_found = false;
    string valid_bills[NUM_DENOMS] = {"5", "10", "20", "50", "100", "200", "500", "1000", "2000", "5000", "10000"};
    for (int i = 0; i < 11; i++)
    {
        if (valid_bills[i] == bill)
        {
            bill_found = true;
        }
    }
    return bill_found;
}

//this function is implemented for environments that does not recognise min()
int min(unsigned int a, unsigned int b)
{
    int smaller_num;
    if (a > b)
    {
        smaller_num = b;
    }
    else
    {
        smaller_num = a;
    }
    return smaller_num;
}
// a recursion function to check for refund capability
bool refund_possible(unsigned int Amount, int Index, Bank *bank)
{
    // this result saves thte bool value for return at the end of function
    bool result = false;
    // the list of accepted denominations put in order to check from high to low to minimise the number of coins returned
    int valid_bills[NUM_DENOMS] = {10000, 5000, 2000, 1000, 500, 200, 100, 50, 20, 10, 5};
    // this occurs when the refund is possible
    if (Amount == 0)
        result = true;
    //this occurs when there is no way to refund the desired amount(including not having the right coin for it)
    else if (Index >= NUM_DENOMS)
        result = false;
    else{
        // pick the maximum number of coins available or the refund needed
        int Range = min(bank->getCoin(Index)->getCount(), Amount / valid_bills[Index]);
        // the recursion occurs to find all possible refund method
        for (int i = Range; i >= 0 && !result; i--)
        {
            // this assumes the amount of money left not refunded with i coins refunded, it will not affect the Amount variable through for loop
            int RemainingAmount = Amount - (i * valid_bills[Index]);
            // recursion to the next denomination
            result = refund_possible(RemainingAmount, Index + 1, bank);
        }
    }
    
    return result;
}
// a modified version of refund_possible, added the ability to print out the coins and reduce the coins in bank accordingly
bool refund(unsigned int Amount, int Index, Bank *bank)
{
    // this result saves thte bool value for return at the end of function
    bool result = false;
    // the list of accepted denominations put in order to check from high to low to minimise the number of coins returned
    int valid_bills[NUM_DENOMS] = {10000, 5000, 2000, 1000, 500, 200, 100, 50, 20, 10, 5};
    // this occurs when the refund is possible
    if (Amount == 0)
        result = true;
    //this occurs when there is no way to refund the desired amount(including not having the right coin for it)
    else if (Index >= NUM_DENOMS)
        result = false;
    else{
        // pick the maximum number of coins available or the refund needed
        int Range = min(bank->getCoin(Index)->getCount(), Amount / valid_bills[Index]);
        // the recursion occurs to find all possible refund method
        for (int i = Range; i >= 0 && !result; i--)
        {
            // this assumes the amount of money left not refunded with i coins refunded, it will not affect the Amount variable through for loop
            int RemainingAmount = Amount - (i * valid_bills[Index]);
            // recursion to the next denomination
            result = refund(RemainingAmount, Index + 1, bank);
            if (result)
            {
                // the return count is useful when multiple coins of same value is refunded
                int return_count = i;
                while (return_count > 0)
                {
                    // identify and print the coin in the right format
                    if (valid_bills[Index] < 100)
                    {
                        cout << valid_bills[Index];
                        cout << "c ";
                        bank->getCoin(Index)->addCount(-1);
                    }
                    else
                    {
                        cout << "$";
                        cout << valid_bills[Index] / 100;
                        cout << " ";
                        bank->getCoin(Index)->addCount(-1);
                    }
                    return_count--;
                }
                
            }
        }
    }
    
    return result;
}

void cancel_purchase(vector<int> paid_list, Bank *bank)
{
    // iterate through the paid list(a vector)
    unsigned int vecsize = paid_list.size();
    for (unsigned int i = 0; i < vecsize; i++)
    {
        // return the coins for change, taken from the bank
        bank->getCoinByCent(paid_list.at(i))->addCount(-1);
    }
}

void purchase(FoodItem *curr, int dollars, int cents, Bank *bank)
{
    //paid_bills is used to save the coins that was paid, saved in a vector as number of coins is unknown
    vector<int> paid_bills = {};
    //initialize the price as an integer in cents
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

        //take bills as string instead of int to scan for empty lines
        string input;
        std::getline(cin, input);
        input.erase(input.find_last_not_of(" \t\r\n\v\f") + 1);

        if (cin.eof() || input.length() == 0)
        {
            cout << endl << "Purchase cancelled!\n";
            //set the money needed to pay to 0 to end the payment cycle
            toPay = 0;
            cancel_purchase(paid_bills, bank);
        }
        // identify denomination
        else if (is_valid_bill(input) == false || Helper::isNumber(input) == false)
        {
            cout << "Error: invalid denomination encountered.\n";
        }
        // add coin to bank + add coin to paid list
        else
        {
            // change the input string to int for calculation
            int payment = std::stoi(input);
            // add the paid coin to the bank, may be needed for change later
            bank->getCoinByCent(payment)->addCount(1);
            paid_bills.insert(paid_bills.begin(), payment);
            toPay -= payment;
        }
    }

    // the toPay value can be negative so reverse it to postive for refund
    toPay = 0 - toPay;
    if (toPay > 0)
    {
        //check if it is possible to refund with the coins in bank before performing the payment to avoid false behaviour
        
        if (refund_possible(toPay, 0, bank))
        {
            cout << "Your change is ";
            refund(toPay, 0, bank);
            cout << "\n";
            // reduce the amount of meal available by 1
            curr->onHand--;
        }
        else
        {
            cout << "Insufficient change in system. Purchase cancelled.\n";
            cancel_purchase(paid_bills, bank);
        }
    }
    // this happens when there is no change
    else
    {
        curr->onHand--;
    }
}
//this function handles the meal choosing option
void pickMeal(LinkedList *list, Bank *bank)
{
    cout << "Purchase Meal:\n";
    cout << "-------------\n";
    cout << "Please enter the ID of the food you wish to purchase: ";
    // the choice is received as a string since the food id was stored as a string
    string choice;
    //this combination of getline and .erase was to implement the "Enter key to cancel" requirement and ensure smooth opera
    std::getline(cin, choice);
    choice.erase(choice.find_last_not_of(" \t\r\n\v\f") + 1);

    FoodItem *curr = list->get(choice);

    //detect if the input file ends, the user press ctrl+D or enter a blank line
    if (cin.eof() || choice.length() == 0)
    {
        cout << endl << "Purchase cancelled!";
    }
    //if the food is found in the saved linked list, curr points to that food object, onHand means how many dishes available
    else if (curr != nullptr && curr->onHand > 0)
    {
        
        cout << "You have selected \"" << curr->name << " - " << curr->description << ".\"\n";
        cout << "This will cost you $ " << std::to_string(curr->price->dollars) << "." ;
        //specify to print 5 cents in the correct format
        if(curr->price->cents < 10){
            cout << "0" << std::to_string(curr->price->cents) << ".\n";
        }
        else{
            cout << std::to_string(curr->price->cents) << ".\n";
        }
        cout << "Please hand over the money - type in the value of each note/coin in cents.\n";
        cout << "Please enter ctrl-D or enter on a new line to cancel this purchase.\n";
        purchase(curr, curr->price->dollars, curr->price->cents, bank);
    }
    else
    {
        cout << "The ID is invalid or there is no dish left of the ID\n";
        pickMeal(list, bank);
        // print error message and let user choose another dish
    }
}
// Compiling terminal code
// g++ -Wall -Werror -std=c++14 -g -O -o ftt coin.cpp node.cpp linkedList.cpp ftt.cpp bank.cpp helper.cpp fileLoader.cpp