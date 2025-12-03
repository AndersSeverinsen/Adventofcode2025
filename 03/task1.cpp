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

void task1(string name, long long expected, bool verbose = false) {
    cout << "Task 1" << endl;
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
        int largest_joltage = 0;
        int largest_joltage_index = 0;
        for (int j = 0; j < line.size(); j++) {
            int digit = (int)line[j] - 48;
            if (digit > largest_joltage && j < line.size() - 1) {
                largest_joltage = digit;
                largest_joltage_index = j;
            }
        }
        int second_largest_joltage = 0;
        for (int j = largest_joltage_index + 1; j < line.size(); j++) {
            int digit = (int)line[j] - 48;
            if (digit > second_largest_joltage) {
                second_largest_joltage = digit;
            }
        }
        int number = largest_joltage * 10 + second_largest_joltage;
        if (verbose) {
            cout << number << endl;
        }
        sum += number;
    }
    Input.close();
    cout << "Result: " << sum << endl;
    assert_equal(expected, sum);
}

int main() {
    task1("03-sample", 357, true);
    task1("03", 17316, false);
    return 0;
}