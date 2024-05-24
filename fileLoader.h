#ifndef FILELOADER_H
#define FILELOADER_H
#include "coin.h"
#include "node.h"
#include "linkedList.h"
#include "bank.h"
#include "helper.h"
#include <fstream>

#define PRICE_DELIMITTER "."
#define FOOD_DELIMITTER "|"

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;

class FileLoader
{
public:
    bool readCoinData(string coinsFile, Bank *bank);
    bool readFoodData(string foodsFile, LinkedList *list);
    void writeCoinData(string coinsFile, Bank *bank);
    void writeFoodData(string foodsFile, LinkedList *list);
};

#endif // FILEREADER_H