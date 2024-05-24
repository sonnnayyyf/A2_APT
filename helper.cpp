#include "helper.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

Helper::Helper() {}
// Some functions were taken from A1
bool Helper::isNumber(string s)
{
    bool isNumber = false;
    try
    {
        std::stoi(s);
        isNumber = true;
    }
    catch (const std::invalid_argument &e)
    {
        isNumber = false;
    }
    return isNumber;
}

void Helper::splitString(string s, vector<string> &tokens, string delimeter)
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

void Helper::printInvalidInput(string str)
{
    cout << "Invalid input! " << str << endl;
}

string Helper::readInput()
{
    string input;
    std::getline(std::cin, input);
    std::cout << std::endl;

    return input;
}

void Helper::removeWhitespace(std::string &str)
{
    str.erase(0, str.find_first_not_of(" \t\n\r\f\v"));
    str.erase(str.find_last_not_of(" \t\n\r\f\v") + 1);

    // Check if the string is not empty
    if (!str.empty())
    {
        // Check if the last character is a newline character
        if (str.back() == '\n')
        {
            // Remove the last character
            str.pop_back();
        }
    }
}
