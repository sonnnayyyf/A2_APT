#include "helper.h"

using std::string;
using std::vector;

Helper::Helper() {}

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
        isNumber = true;
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
