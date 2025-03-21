#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <string>
#include <cassert>
#include <sstream>
#include <vector>
#include <iostream>
#include <string.h>
#include <random>

class Helper
{
private:
    Helper();

public:
    static bool isNumber(std::string s);

    static void splitString(std::string s, std::vector<std::string> &tokens, std::string delimeter);

    static void printInvalidInput(std::string str);

    static std::string readInput();

    static void removeWhitespace(std::string &str);
};
#endif // HELPER_H