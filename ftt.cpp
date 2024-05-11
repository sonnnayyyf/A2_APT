#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "linkedList.h"
#include "bank.h"
#include "string.h"
#include "fileLoader.h"

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
    /* validate command line arguments */
    // TODO
    if (argc != EXPECTED_ARGUMENTS)
    {
        cout << "Invalid number of command line arguments given!" << endl;
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
            list->printItems();
            bank->displayBalance();

            
        }
        else
        {
            cout << "Files could not be loaded. Aborting Program" << endl;
        }
    }

    return EXIT_SUCCESS;
}

// Compiling terminal code
// g++ -Wall -Werror -std=c++14 -g -O -o ftt coin.cpp node.cpp linkedList.cpp ftt.cpp bank.cpp helper.cpp fileLoader.cpp
