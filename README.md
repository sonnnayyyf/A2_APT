# Repository for Assignment 2 - Advanced Programming Technique (Semester 1, 2024)

Tran Hoang Son - s3978450

Nguyen Huu Khoi - s3979411

Wai Yan Lin - s3963096

Contributions:

Wai Yan Lin - Linked list, bank, node, implementation. Bash file for running tests for loading in data to the program. Tests for loading in data from foods and coins file. Implemented display balance and display menu functions. Revised functions to not use returns. Making the make file.

Tran Hoang Son - Input validation, add function, find highest id, remove function and tests for them. Debugging add and remove. Sorting out the excel weekly tracking sheet to become informative for all members.

Nguyen Huu Khoi - Implementation of purchase function, refund function, purchase cancel function, save file function. Write tests for purchase functions (including purchase cancel and refund). 

 Compiling terminal code:
 g++ -Wall -Werror -std=c++14 -g -O -o ftt coin.cpp node.cpp linkedList.cpp ftt.cpp bank.cpp helper.cpp fileLoader.cpp vendingMachine.cpp

 Memory Leak Checks:
 valgrind --leak-check=full --show-leak-kinds=all ./ftt foods.dat coins.dat
 valgrind --track-origins=yes ./ftt foods.dat coins.dat
