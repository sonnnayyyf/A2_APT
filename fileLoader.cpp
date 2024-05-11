#include "fileLoader.h"

bool FileLoader::loadCoinData(string coinsFile, Bank *bank)
{
    int success = false;
    int reading = true;
    int count = 0;
    int cents = 0;
    string coinItem = "";

    // Open the coins file
    ifstream inputFile(coinsFile);

    // Checks if files exists
    if (inputFile.is_open())
    {
        while (getline(inputFile, coinItem) && reading && !inputFile.eof())
        {
            std::vector<std::string> token = {};
            Helper::splitString(coinItem, token, DELIM);

            // Check if the string was split into two pieces meaning the existence of ","
            if (token.size() == 2)
            {
                string centsStr = token[0];
                string countStr = token[1];
                if (Helper::isNumber(centsStr) && Helper::isNumber(countStr))
                {
                    cents = std::stoi(centsStr);
                    count = std::stoi(countStr);

                    if (cents > 0 && count > 0)
                    {
                        bank->manageBalance(cents, ADD, count);
                        success = true;
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
        }
    }
    else
    {
        cout << "File could not be opened" << endl;
    }
    return success;
}

bool FileLoader::loadFoodData(string foodsFile, LinkedList *list)
{
    int success = false;
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
            Helper::splitString(foodItem, token, FOOD_DELIMITTER);

            // Check if token are missing or more
            // Checking if the string is split with the "|" delimitter properly
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
                    Helper::splitString(foodPrice, token, PRICE_DELIMITTER);

                    // Validate Price
                    // Checking if the price can be split with "." delimitter
                    // cout << "INSIDE | CHECK" << endl;
                    if (token.size() == 2)
                    {
                        string dollarStr = token[0];
                        string centsStr = token[1];

                        // Checking if the 2 strings are valid numbers
                        if (Helper::isNumber(dollarStr) && Helper::isNumber(centsStr))
                        {
                            dollars = std::stoi(token[0]);
                            cents = std::stoi(token[1]);

                            // Check if values are below zero
                            if (dollars >= 0 && cents >= 0)
                            {
                                // Checking for duplicates
                                if (list->get(foodId) == nullptr)
                                {
                                    FoodItem *item = new FoodItem(foodId, foodName, foodDesc, new Price((unsigned)dollars, (unsigned)cents), DEFAULT_FOOD_STOCK_LEVEL);
                                    list->addBack(item);
                                    success = true;
                                }
                                else
                                {
                                    cout << "Invalid Input. Item already exists in menu" << endl;
                                    reading = false;
                                }
                            }
                            else
                            {
                                cout << "Price entered must be greater than or equal to zero" << endl;
                                reading = false;
                            }
                        }
                        else
                        {
                            cout << "Price read is not a number" << endl;
                            reading = false;
                        }
                    }
                    else
                    {
                        cout << "Price needs to be in the format D.C where D is dollars and C is cents" << endl;
                        reading = false;
                    }
                }
                else
                {
                    cout << "Incorrect food data length" << endl;
                    cout << "ID max length: " << IDLEN << endl;
                    cout << "Name max length: " << NAMELEN << endl;
                    cout << "Description max length: " << DESCLEN << endl;
                    reading = false;
                }
            }
            else
            {
                cout << "Missing food data" << endl;
                reading = false;
            }
        }
    }
    else
    {
        cout << "File could not be opened" << endl;
    }

    // If any of the validation checks fail return false
    // If all checks pass and data is read return true
    return success;
}

void FileLoader::enterFoodData(string foodsFile, LinkedList *list){

}
void FileLoader::enterCoinData(string coinsFile, Bank* bank){
    
}