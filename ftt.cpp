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
#include "vendingMachine.h"

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
        Bank *bank = new Bank();
        FileLoader fileLoader;
        VendingMachine *vendingMachine = new VendingMachine(list, bank, fileLoader);

        if (vendingMachine->loadVendingMachine(foodsFile, coinsFile))
        {
            bool menuRunning = true;
            cout << mainMenu;
            string input = "";
            std::getline(cin, input);

            while (menuRunning && !input.empty())
            {
                input.erase(input.find_last_not_of(" \t\r\n\v\f") + 1);
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
                                vendingMachine->displayItems();
                            }
                            else if (choice == 2)
                            {
                                vendingMachine->purchaseItem();
                            }
                            else if (choice == 3)
                            {
                                vendingMachine->saveData("foodsTest.dat", "coinsTest.dat");
                                cout << "Data saved and program exiting." << endl;
                                menuRunning = false;
                            }
                            else if (choice == 4)
                            {
                                vendingMachine->addItem();
                            }
                            else if (choice == 5)
                            {
                                vendingMachine->removeItem();
                            }
                            else if (choice == 6)
                            {
                                vendingMachine->displayBalance();
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
                        std::getline(cin, input);
                    }
                }
            }
        }
        else
        {
            Helper::printInvalidInput("Files could not be loaded. Aborting Program.");
        }
        delete vendingMachine;
    }

    return EXIT_SUCCESS;
}

// Compiling terminal code
// g++ -Wall -Werror -std=c++14 -g -O -o ftt coin.cpp node.cpp linkedList.cpp ftt.cpp bank.cpp helper.cpp fileLoader.cpp vendingMachine.cpp