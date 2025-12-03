#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <fstream>
#include <assert.h>
#include <string>

using namespace std;

void assert_equal(long long expected, long long actual) {
    if (expected != actual) {
        cerr << "Assert failed! Expected: " << expected << ", but got: " << actual << endl;
        throw std::exception();
    }
}

long long largest_joltage(string line, int length, long long num, int largest_joltage_index, bool verbose = false) {
    int ith_largest_joltage = 0;
    int ith_largest_joltage_index = 0;
    for (int j = largest_joltage_index; j < line.size(); j++) {
        int digit = (int)line[j] - 48;
        if (digit > ith_largest_joltage && j < line.size() - length) {
            ith_largest_joltage = digit;
            ith_largest_joltage_index = j;
        }
    }
    long long number = num * 10 + ith_largest_joltage;
    if (length == 0) {
        if (verbose) {
            cout << number << endl;
        }
        return number;
    }
    return largest_joltage(line, length-1, number, ith_largest_joltage_index+1, verbose);
}

void task1(string name, long long expected, bool verbose = false) {
    cout << "Task 2" << endl;
    cout << "Input: " << name << endl;
    string fileame = name + ".txt";
    ifstream Input(fileame);
    if (!Input.is_open()) {
        cerr << "Error opening the file!";
        return;
    }
    string line;
    long long sum = 0;
    while (getline (Input, line)) {
        long long number = largest_joltage(line, 11, 0, 0, verbose);
        sum += number;
    }
    Input.close();
    cout << "Result: " << sum << endl;
    assert_equal(expected, sum);
}

int main() {
    task1("03-sample", 3121910778619, true);
    task1("03", 171741365473332, false);
    return 0;
}