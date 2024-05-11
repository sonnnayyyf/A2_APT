#!/bin/bash

# Compile the C++ program
g++ -Wall -Werror -std=c++14 -g -O -o ftt coin.cpp node.cpp linkedList.cpp ftt.cpp bank.cpp helper.cpp fileLoader.cpp

# Go to tests directory
# cd ./tests

# Check if compilation was successful
if [ $? -ne 0 ]; then
    echo "Compilation failed"
    exit 1
fi

# Function to run a test
run_test() {
    local args1="$1"
    local args2="$2"
    local input_file="$3"
    local expected_output_file="$4"
    local output_file="$5"

    echo "Running test $6"
    ./ftt $args1 $args2 < "$input_file" > "$output_file"
    # diff -w -y "$expected_output_file" "$output_file"
    if diff -q "$expected_output_file" "$output_file" >/dev/null; then
        echo "Test $6 passed"
    else
        echo "Test $6 failed"
    fi
    echo ""
}

# Test 1
# Testing for invalid command line argurments like having too many or too little
run_test "fewa" "" "./tests/input1.txt" "./tests/expected1.txt" "./tests/output1.txt" 1

# Test 2
# Testing for invalid files entered as argurmnets. If file does not exist or cannot be read.
# Testing for both loading food and coins
run_test "fewa" "fewa" "./tests/input2.txt" "./tests/expected2.txt" "./tests/output2.txt" 2.1
run_test "foods.dat" "fewa" "./tests/input2.txt" "./tests/expected2.txt" "./tests/output2.txt" 2.2
run_test "fewa" "coins.dat" "./tests/input2.txt" "./tests/expected2.txt" "./tests/output2.txt" 2.3

# Test 3
# Testing if there was no end of line character in the data file
# Testing for both loading food and coins
run_test "./tests/input3.txt" "coins.dat" "./tests/noinput.txt" "./tests/expected3.txt" "./tests/output3.txt" 3.1
run_test "foods.dat" "./tests/input3.txt" "./tests/noinput.txt" "./tests/expected3.txt" "./tests/output3.txt" 3.2

# Test 4
# Food data should be ID|NAME|DESCRIPTION|PRICE
# Check if there is any more or more details
# Checks if it's in the right format as well has to be separated by "|"
# Only checking for foodData
run_test "./tests/input4.1.txt" "coins.dat" "./tests/noinput.txt" "./tests/expected4.txt" "./tests/output4.1.txt" 4.1
run_test "./tests/input4.2.txt" "coins.dat" "./tests/noinput.txt" "./tests/expected4.txt" "./tests/output4.2.txt" 4.2
run_test "./tests/input4.3.txt" "coins.dat" "./tests/noinput.txt" "./tests/expected4.txt" "./tests/output4.3.txt" 4.3

# Test 5
# Details in FoodData has a max legnth check if any exceeds this
# Only checking for foodData
# We will check in order ID, Name, and then description, price has no max length mentioned
run_test "./tests/input5.1.txt" "coins.dat" "./tests/noinput.txt" "./tests/expected5.txt" "./tests/output5.1.txt" 5.1
run_test "./tests/input5.2.txt" "coins.dat" "./tests/noinput.txt" "./tests/expected5.txt" "./tests/output5.2.txt" 5.2
run_test "./tests/input5.3.txt" "coins.dat" "./tests/noinput.txt" "./tests/expected5.txt" "./tests/output5.3.txt" 5.3

# Test 6
# Price correct format check
# Has to be separated by "."
run_test "./tests/input6.1.txt" "coins.dat" "./tests/noinput.txt" "./tests/expected6.txt" "./tests/output6.1.txt" 6.1
run_test "./tests/input6.2.txt" "coins.dat" "./tests/noinput.txt" "./tests/expected6.txt" "./tests/output6.2.txt" 6.2

# Test 7
# Price has to be a number check
run_test "./tests/input7.txt" "coins.dat" "./tests/noinput.txt" "./tests/expected7.txt" "./tests/output7.txt" 7


# Test 8
# Checking is price is a number greater than 0
run_test "./tests/input8.1.txt" "coins.dat" "./tests/noinput.txt" "./tests/expected8.txt" "./tests/output8.1.txt" 8.1
run_test "./tests/input8.2.txt" "coins.dat" "./tests/noinput.txt" "./tests/expected8.txt" "./tests/output8.2.txt" 8.2

# Test 9 
# Checking for duplicates in data using the ID of foodData
run_test "./tests/input9.txt" "coins.dat" "./tests/noinput.txt" "./tests/expected9.txt" "./tests/output9.txt" 9

# Test 10 
# Menu that's displayed when everything goes correctly
# and when its written back to the file
# NEED TO BE IMPLEMENTED
# run_test "foods.dat" "coins.dat" "./tests/input10.txt" "./tests/expected10.txt" "./tests/output10.txt" 10
# diff -w -y "./tests/expected_food" "./foods.dat"

# Test 11
















