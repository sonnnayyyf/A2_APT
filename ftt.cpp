#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "LinkedList.h"
#include <string.h>

#define EXPECTED_ARGUMENTS 3
#define NUM_OF_DENOMS

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;

int readFoodData(string foodsFile, LinkedList &list);

int readCoinData(string coinsFile, Coin *coinsArray[]);

void splitString(string s, vector<string> &tokens, string delimeter);

string readInput();

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
        cout << "Invalid number of arguments given!" << endl;
    }
    else
    {
        string foodsFile = argv[1];
        string coinsFile = argv[2];
        LinkedList list;

        Coin *coinsArray[NUM_DENOMS];

        readFoodData(foodsFile, list);
        readCoinData(coinsFile, coinsArray);

        list.printItems();
    }

    return EXIT_SUCCESS;
}

int readFoodData(string foodsFile, LinkedList &list)
{
    int success = 0;
    bool reading = true;
    int dollars = 0;
    int cents = 0;
    string foodItem = "";

    ifstream inputFile(foodsFile);

    if (inputFile.is_open())
    {
        while (getline(inputFile, foodItem) && reading && !inputFile.eof())
        {
            std::vector<std::string> token = {};
            splitString(foodItem, token, "|");

            // Check if token are missing or more
            // If there are 4 token contiue
            if (token.size() == 4)
            {
                string foodId = token[0];
                string foodName = token[1];
                string foodDesc = token[2];
                string foodPrice = token[3];

                // VALIDATION CHECKS
                // Checking lengths of all the strings
                if (foodId.length() == IDLEN && foodName.length() <= NAMELEN && foodDesc.length() <= DESCLEN)
                {
                    // Spliting price into dollars and cents
                    splitString(token[3], token, ".");

                    // Validate Price
                    if (token.size() == 2)
                    {
                        // Check if values can be converted into integers
                        try
                        {
                            dollars = std::stoi(token[0]);
                            cents = std::stoi(token[1]);
                        }
                        catch (const std::invalid_argument &e)
                        {
                            reading = false;
                        }

                        // Check if values are below zero
                        if (dollars < 0 && cents < 0)
                        {
                            reading = false;
                        }
                    }
                    else
                    {
                        reading = false;
                    }
                }
                else
                {
                    reading = false;
                }
                FoodItem *item = new FoodItem(foodId, foodName, foodDesc, new Price((unsigned)dollars, (unsigned)cents), DEFAULT_FOOD_STOCK_LEVEL);
                list.addBack(item);
            }
            else
            {
                reading = false;
            }
        }
    }

    // If file can't be opened return 0
    // If read success return 1
    return success;
}

int readCoinData(string coinsFile, Coin *coinsArray[])
{
    int success = 0;
    int reading = true;
    string coinItem = "";

    // Open the coins file
    ifstream inputFile(coinsFile);

    if (inputFile.is_open())
    {
        while (getline(inputFile, coinItem) && reading && !inputFile.eof())
            cout << coinItem << endl;
    }
    return success;
}

void splitString(string s, vector<string> &tokens, string delimeter)
{
    tokens.clear();
    char *_s = new char[s.length() + 1];
    strcpy(_s, s.c_str());

    char *pch;
    pch = strtok(_s, delimeter.c_str());
    while (pch != NULL)
    {
        tokens.push_back(pch);
        pch = strtok(NULL, delimeter.c_str());
    }
    delete[] _s;
}

string readInput()
{
    string input;
    std::getline(std::cin, input);
    std::cout << std::endl;

    return input;
}