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

                    if (cents >= 0 && count >= 0)
                    {

                        Coin *coin = bank->getCoinByCent(cents);
                        if (!coin->isInitialized())
                        {
                            coin->addCount(count);
                            coin->initialize();
                            success = true;
                        }
                        else
                        {
                            Helper::printInvalidInput("This Denomination has already been initialized. Cannot initialize again.");
                        }
                    }
                    else
                    {
                        Helper::printInvalidInput("Denom and count inputs must be greater than or equal to zero.");
                        reading = false;
                        success = false;
                    }
                }
                else
                {
                    Helper::printInvalidInput("Denom and count inputs must be numbers.");
                    reading = false;
                    success = false;
                }
            }
            else
            {
                Helper::printInvalidInput(
                    "Input is not correctly formatted to read coins. Correct format is D,C D for denomination and C for count.");
                reading = false;
                success = false;
            }
        }
        if (std::cin.eof())
        {
            cout << endl;
            cout << endl;
            cout << "End Of File character inputted" << endl;
            success = false;
        }
    }
    else
    {
        Helper::printInvalidInput("File not found or could not be opened.");
        success = false;
    }
    // closing file
    inputFile.close();
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
                                    Helper::printInvalidInput("Food item with input ID already exists in the system.");
                                    reading = false;
                                    success = false;
                                }
                            }
                            else
                            {
                                Helper::printInvalidInput("Price entered must be greater than or equal to zero.");
                                reading = false;
                                success = false;
                            }
                        }
                        else
                        {
                            Helper::printInvalidInput("Price input must be a number.");
                            reading = false;
                            success = false;
                        }
                    }
                    else
                    {
                        Helper::printInvalidInput("Price written in incorrect format. The correct format should be DD.CC where DD is dollars and CC is cents.");
                        reading = false;
                        success = false;
                    }
                }
                else
                {
                    Helper::printInvalidInput("File details exceed max length.");
                    cout << "ID max length: " << IDLEN << endl;
                    cout << "Name max length: " << NAMELEN << endl;
                    cout << "Description max length: " << DESCLEN << endl;
                    reading = false;
                    success = false;
                }
            }
            else
            {
                Helper::printInvalidInput("File missing details or details are not written in the correct format.");
                success = false;
            }
        }

        if (std::cin.eof())
        {
            cout << endl;
            cout << endl;
            cout << "End Of File character inputted" << endl;
            success = false;
        }
    }
    else
    {
        Helper::printInvalidInput("File not found or could not be opened.");
        success = false;
    }

    // If any of the validation checks fail return false
    // If all checks pass and data is read return true
    // Closing file
    inputFile.close();
    return success;
}

void FileLoader::enterFoodData(string foodsFile, LinkedList *list)
{
    ofstream inputFile(foodsFile);
    Node *curr = list->getHead();
    while (curr != nullptr)
    {
        inputFile << curr->foodItem->writeItem() << endl;
        curr = curr->next;
    }

    inputFile.close();
}
void FileLoader::enterCoinData(string coinsFile, Bank *bank)
{
    ofstream inputFile(coinsFile);
    Coin *current_coin = nullptr;
    for (int i = 0; i < NUM_DENOMS; i++)
    {
        current_coin = bank->getCoin(i);
        inputFile << current_coin->getDenom() << "," << current_coin->getCount() << endl;
    }
    inputFile.close();
}