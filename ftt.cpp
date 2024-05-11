#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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

// Compiling terminal code
// g++ -Wall -Werror -std=c++14 -g -O -o ftt coin.cpp node.cpp linkedList.cpp ftt.cpp bank.cpp helper.cpp fileLoader.cpp
