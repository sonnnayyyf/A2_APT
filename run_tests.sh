#!/bin/bash

# Compile the C++ program
g++ -Wall -Werror -std=c++14 -g -O -o ftt coin.cpp node.cpp linkedList.cpp ftt.cpp bank.cpp helper.cpp fileLoader.cpp vendingMachine.cpp

# Go to loadingData_tests directory
# cd ./loadingData_tests

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








compare_coins() {
    local expected_output_file="$1"
    local output_file="$2"
    local num="$3"
    if diff -w -y "$expected_output_file" "$output_file" >/dev/null; then
        echo "Test "$num" coins passed"
    else
        echo "Test "$num" coins failed"
    fi
    echo ""

}

# The tests below mainly focus only reading food data from a file
echo "Running loading data tests"
echo "------------------------------------"
echo ""

# Test 1
# Testing for invalid command line argurments like having too many or too little
run_test "fewa" "" "./loadingData_tests/input1.txt" "./loadingData_tests/expected1.txt" "./loadingData_tests/output1.txt" 1

# Test 2
# Testing for invalid files entered as argurmnets. If file does not exist or cannot be read.
# Testing for both loading food and coins
run_test "fewa" "fewa" "./loadingData_tests/input2.txt" "./loadingData_tests/expected2.txt" "./loadingData_tests/output2.txt" 2.1
run_test "foods.dat" "fewa" "./loadingData_tests/input2.txt" "./loadingData_tests/expected2.txt" "./loadingData_tests/output2.txt" 2.2
run_test "fewa" "coins.dat" "./loadingData_tests/input2.txt" "./loadingData_tests/expected2.txt" "./loadingData_tests/output2.txt" 2.3

# Test 3
# Testing if there was no end of line character in the data file
# Testing for both loading food and coins
run_test "./loadingData_tests/input3.txt" "coins.dat" "./loadingData_tests/noinput.txt" "./loadingData_tests/expected3.txt" "./loadingData_tests/output3.txt" 3.1
run_test "foods.dat" "./loadingData_tests/input3.txt" "./loadingData_tests/noinput.txt" "./loadingData_tests/expected3.txt" "./loadingData_tests/output3.txt" 3.2

# Test 4
# Food data should be ID|NAME|DESCRIPTION|PRICE
# Check if there is any more or more details
# Checks if it's in the right format as well has to be separated by "|"
# Only checking for foodData
run_test "./loadingData_tests/input4.1.txt" "coins.dat" "./loadingData_tests/noinput.txt" "./loadingData_tests/expected4.txt" "./loadingData_tests/output4.1.txt" 4.1
run_test "./loadingData_tests/input4.2.txt" "coins.dat" "./loadingData_tests/noinput.txt" "./loadingData_tests/expected4.txt" "./loadingData_tests/output4.2.txt" 4.2
run_test "./loadingData_tests/input4.3.txt" "coins.dat" "./loadingData_tests/noinput.txt" "./loadingData_tests/expected4.txt" "./loadingData_tests/output4.3.txt" 4.3

# Test 5
# Details in FoodData has a max length check if any exceeds this
# Only checking for foodData
# We will check in order ID, Name, and then description, price has no max length mentioned
run_test "./loadingData_tests/input5.1.txt" "coins.dat" "./loadingData_tests/noinput.txt" "./loadingData_tests/expected5.txt" "./loadingData_tests/output5.1.txt" 5.1
run_test "./loadingData_tests/input5.2.txt" "coins.dat" "./loadingData_tests/noinput.txt" "./loadingData_tests/expected5.txt" "./loadingData_tests/output5.2.txt" 5.2
run_test "./loadingData_tests/input5.3.txt" "coins.dat" "./loadingData_tests/noinput.txt" "./loadingData_tests/expected5.txt" "./loadingData_tests/output5.3.txt" 5.3

# Test 6
# Price correct format check
# Has to be separated by "."
run_test "./loadingData_tests/input6.1.txt" "coins.dat" "./loadingData_tests/noinput.txt" "./loadingData_tests/expected6.txt" "./loadingData_tests/output6.1.txt" 6.1
run_test "./loadingData_tests/input6.2.txt" "coins.dat" "./loadingData_tests/noinput.txt" "./loadingData_tests/expected6.txt" "./loadingData_tests/output6.2.txt" 6.2

# Test 7
# Price has to be a number check
run_test "./loadingData_tests/input7.txt" "coins.dat" "./loadingData_tests/noinput.txt" "./loadingData_tests/expected7.txt" "./loadingData_tests/output7.txt" 7


# Test 8
# Checking is price is a number greater than 0
run_test "./loadingData_tests/input8.1.txt" "coins.dat" "./loadingData_tests/noinput.txt" "./loadingData_tests/expected8.txt" "./loadingData_tests/output8.1.txt" 8.1
run_test "./loadingData_tests/input8.2.txt" "coins.dat" "./loadingData_tests/noinput.txt" "./loadingData_tests/expected8.txt" "./loadingData_tests/output8.2.txt" 8.2

# Test 9 
# Checking for duplicates in data using the ID of foodData
run_test "./loadingData_tests/input9.txt" "coins.dat" "./loadingData_tests/noinput.txt" "./loadingData_tests/expected9.txt" "./loadingData_tests/output9.txt" 9



# The tests below focus on reading coins data from a file

# Test 10
# Testing if the price data is written in the correct format seperated by a ","
# It should be in the format denomination,count
run_test "foods.dat" "./loadingData_tests/input10.txt" "./loadingData_tests/noinput.txt" "./loadingData_tests/expected10.txt" "./loadingData_tests/output10.txt" 10

# Test 11
# Check if price read can be converted into a number
run_test "foods.dat" "./loadingData_tests/input11.txt" "./loadingData_tests/noinput.txt" "./loadingData_tests/expected11.txt" "./loadingData_tests/output11.txt" 11

# Test 12
# Check if price values are greater than or equal to zero
run_test "foods.dat" "./loadingData_tests/input12.txt" "./loadingData_tests/noinput.txt" "./loadingData_tests/expected12.txt" "./loadingData_tests/output12.txt" 12

# Test 13
# Checking for duplicate coins entries in data file
# We handle this by only taking the data from the first one encountered and skip the rest
run_test "foods.dat" "./loadingData_tests/input13.txt" "./loadingData_tests/commands13.txt" "./loadingData_tests/expected13.txt" "./loadingData_tests/output13.txt" 13


echo "Running purchase tests"
echo "------------------------------------"
echo ""

run_test "foods.dat" "coins.dat" "./purchase_tests/purchase1.input" "./purchase_tests/purchase1.expected_output" "./output.txt" 1
run_test "foods.dat" "coins.dat" "./purchase_tests/purchase2.input" "./purchase_tests/purchase2.expected_output" "./output.txt" 2
run_test "foods.dat" "coins.dat" "./purchase_tests/purchase3.input" "./purchase_tests/purchase3.expected_output" "./output.txt" 3
run_test "foods.dat" "coins.dat" "./purchase_tests/purchase4.input" "./purchase_tests/purchase4.expected_output" "./output.txt" 4
run_test "foods.dat" "coins.dat" "./purchase_tests/purchase5.input" "./purchase_tests/purchase5.expected_output" "./output.txt" 5
run_test "foods.dat" "coins.dat" "./purchase_tests/purchase6.input" "./purchase_tests/purchase6.expected_output" "./output.txt" 6
run_test "foods.dat" "coins.dat" "./purchase_tests/purchase7.input" "./purchase_tests/purchase7.expected_output" "./output.txt" 7
run_test "foods.dat" "coins.dat" "./purchase_tests/purchase8.input" "./purchase_tests/purchase8.expected_output" "./output.txt" 8
run_test "foods.dat" "coins.dat" "./purchase_tests/purchase9.input" "./purchase_tests/purchase9.expected_output" "./output.txt" 9
run_test "foods.dat" "coins.dat" "./purchase_tests/purchase10.input" "./purchase_tests/purchase10.expected_output" "./output.txt" 10


 













