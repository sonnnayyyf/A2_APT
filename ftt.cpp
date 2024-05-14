#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
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
 * Make sure free memory and close all files before exiting the program.
 **/

void pickMeal(LinkedList * list, Bank *bank);

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

            while (menuRunning && std::getline(std::cin, input))
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
                            // TODO
                            pickMeal(list, bank);
                        }
                        else if (choice == 3)
                        {
                            // TODO
                            fileLoader.enterFoodData(foodsFile, list);
                            fileLoader.enterCoinData(coinsFile, bank);
                            menuRunning = false;
                        }
                        else if (choice == 4)
                        {
                            // TODO
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
                            // TODO
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
                cout << mainMenu;
            }

            if (std::cin.eof())
            {
                cout << endl;
                cout << endl;
                Helper::printInvalidInput("End Of File character inputted.");
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

bool is_valid_bill(int bill){
    bool bill_found = false;
    int valid_bills[NUM_DENOMS]={5, 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000};
    for(int i = 0; i < 11; i++){
        if(valid_bills[i] == bill){bill_found = true;}
    }
    return bill_found;
}

bool refund_possible(int Amount, int Index=0, Bank* bank)
{
    int valid_bills[NUM_DENOMS]={5, 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000};
    if (Amount == 0)
        return true;
    if (Index >= NUM_DENOMS)
        return false;
    int Range = min(bank->getCoin(Index)->getCount(), Amount / valid_bills[Index]);
    for (int i = Range; i >= 0; i--)
    {
        int RemainingAmount = Amount - (i * valid_bills[Index]);
        bool result = refund_possible(RemainingAmount, Index + 1);
        if (result == true)
        {
            return true;
        }    
    }
    return false;
}

bool refund(int Amount, int Index=0, Bank* bank)
{
    int valid_bills[NUM_DENOMS]={5, 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000};
    if (Amount == 0)
        return true;
    if (Index >= NUM_DENOMS)
        return false;
    int Range = min(bank->getCoin(Index)->getCount(), Amount / valid_bills[Index]);
    for (int i = Range; i >= 0; i--)
    {
        int RemainingAmount = Amount - (i * valid_bills[Index]);
        bool result = refund_possible(RemainingAmount, Index + 1);
        if (result == true)
        {
            while(i > 0){
                if(valid_bills[Index] < 100){
                    cout << valid_bills[Index];
                    cout << "c ";
                }
                else{
                    cout << "$";
                    cout << valid_bills[Index] / 100 ;
                    cout << " ";
                }
                i--;
            }
            return true;
        }    
    }
    return false;
}

void cancel_purchase(vector<int> paid_list, Bank* bank){
    for ( int i = 0; i< paid_list.size(); i++){
        DenomIndex index;
            if(payment == FIVE_CENT){
                index = FIVE_CENT_INDEX; 
            }
            else if(payment == TEN_CENT){
                index = TEN_CENT_INDEX;
            }
            else if(payment == TWENTY_CENT){
                index = TWENTY_CENT_INDEX;
            }
            else if(payment == FIFTY_CENT){
                index = FIFTY_CENT_INDEX;
            }
            else if(payment == ONE_DOLLAR){
                index = ONE_DOLLAR_INDEX;
            }
            else if(payment == TWO_DOLLAR){
                index = TWO_DOLLAR_INDEX;
            }
            else if(payment == FIVE_DOLLAR){
                index = FIVE_DOLLAR_INDEX;
            }
            else if(payment == TEN_DOLLAR){
                index = TEN_DOLLAR_INDEX;
            }
            else if(payment == TWENTY_DOLLAR){
                index = TWENTY_DOLLAR_INDEX;
            }
            else if(payment == FIFTY_DOLLAR){
                index = FIFTY_DOLLAR_INDEX;
            }
            else if(payment == HUNDRED_DOLLAR){
                index = HUNDRED_DOLLAR_INDEX;
            }
            bank->getCoin(index)->addCount(-1);
    }
}

void purchase(int dollars, int cents, Bank *bank){
    vector<int> paid_bills = {};
    int toPay = dollars * 100 + cents;
    while (toPay > 0){
        cout << "You still need to give us $ " + std::to_string(toPay / 100) + ".";
        if(toPay % 100 > 9){
            cout << std::to_string(toPay % 100) +":";
        }
        else{
            cout << "0" + std::to_string(toPay % 100) +":";
        }
        int payment;
        cin >> payment;
        if(cin.eof() || std::to_string(payment) == ""){
            cout << "Purchase cancelled!\n";
            cancel_purchase(paid_bills, bank);
        }
        else if(!is_valid_bill(payment)){
            cout << "Error: invalid denomination encountered.\n";
        }
        //identify demon +add coin to bank + add coin to paid list
        else{
            DenomIndex index;
            if(payment == FIVE_CENT){
                index = FIVE_CENT_INDEX; 
            }
            else if(payment == TEN_CENT){
                index = TEN_CENT_INDEX;
            }
            else if(payment == TWENTY_CENT){
                index = TWENTY_CENT_INDEX;
            }
            else if(payment == FIFTY_CENT){
                index = FIFTY_CENT_INDEX;
            }
            else if(payment == ONE_DOLLAR){
                index = ONE_DOLLAR_INDEX;
            }
            else if(payment == TWO_DOLLAR){
                index = TWO_DOLLAR_INDEX;
            }
            else if(payment == FIVE_DOLLAR){
                index = FIVE_DOLLAR_INDEX;
            }
            else if(payment == TEN_DOLLAR){
                index = TEN_DOLLAR_INDEX;
            }
            else if(payment == TWENTY_DOLLAR){
                index = TWENTY_DOLLAR_INDEX;
            }
            else if(payment == FIFTY_DOLLAR){
                index = FIFTY_DOLLAR_INDEX;
            }
            else if(payment == HUNDRED_DOLLAR){
                index = HUNDRED_DOLLAR_INDEX;
            }
            bank->getCoin(index)->addCount(1);
            paid_bills.insert(paid_bills.begin(), payment);
            toPay -= payment;
        }

    }

    if (toPay < 0){
        if(refund_possible(toPay, 0, bank)){
            cout << "Your change is ";
            refund(toPay, 0, bank);
            cout << "\n";
        }
        else{
            cout << "Insufficient change in system. Purchase cancelled.\n";
            cancel_purchase(paid_bills, bank);
        }
    }
}

void pickMeal(LinkedList *list, Bank *bank){
    cout << "Purchase Meal:\n";
    cout << "-------------\n";
    cout << "Please enter the ID of the food you wish to purchase:\n";
    bool foodFound = false;
    string choice;
    cin >> choice;

    FoodItem *curr = list->get(choice);
    if (curr != nullptr && curr->onHand > 0)
    {
        foodFound = true;
        cout << "You have selected \"" << curr->name << " - " << curr->description << ".\"\n";
        cout << "This will cost you $ " << std::to_string(curr->price->dollars) << "." << std::to_string(curr->price->cents) <<".\n";
        cout << "Please hand over the money - type in the value of each note/coin in cents.\n";
        cout << "Please enter ctrl-D or enter on a new line to cancel this purchase.\n";
        purchase(curr->price->dollars, curr->price->cents, bank); 
    }
    else {
        cout << "The ID is invalid or there is no dish left of the ID\n";
        pickMeal(list, bank);
        //print error message
        
    }
}
// Compiling terminal code
// g++ -Wall -Werror -std=c++14 -g -O -o ftt coin.cpp node.cpp linkedList.cpp ftt.cpp bank.cpp helper.cpp fileLoader.cpp
