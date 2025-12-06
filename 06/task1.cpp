#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <fstream>
#include <assert.h>
#include <string>
#include <tuple>

using namespace std;

void assert_equal(long long expected, long long actual) {
    if (expected != actual) {
        cerr << "Assert failed! Expected: " << expected << ", but got: " << actual << endl;
        throw std::exception();
    }
}

void task1(string name, long long expected, int numberOfLines, bool verbose = false) {
    cout << "Task 1" << endl;
    cout << "Input: " << name << endl;
    string fileame = name + ".txt";
    ifstream Input(fileame);
    if (!Input.is_open()) {
        cerr << "Error opening the file!";
        return;
    }
    string line;
    vector<vector<int>> equations;
    long long grand_total = 0;
    int lineCount = 0;
    while (getline (Input, line)) {
        if (numberOfLines > lineCount) {
            vector<int> equation;
            int number = 0;
            bool inNumber = false;
            for (char c : line) {
                if (c == ' ') {
                    if (inNumber) {
                        equation.push_back(number);
                        inNumber = false;
                    }
                    number = 0;
                } else {
                    inNumber = true;
                    number *= 10;
                    number += (int)c - 48;
                }
            }
            if (inNumber) {
                equation.push_back(number);
            }
            if (verbose) {
                cout << lineCount << ": ";
                for (int n : equation) {
                    cout << n << " ";
                }
                cout << endl;
            }
            equations.push_back(equation);
            lineCount++;
        } else {
            int index = 0;
            for (char c : line) {
                if (c == '+') {
                    long long sum = 0;
                    for (int i = 0; i < equations.size(); i++) {
                        sum += equations[i][index];
                        if (verbose) {
                            cout << equations[i][index];
                            if (i == equations.size() - 1) {
                                cout << " = " << sum << endl;
                            } else {
                                cout << " + ";
                            }
                        }
                    }
                    grand_total += sum;
                    index++;
                } else if (c == '*') {
                    long long sum = 1;
                    for (int i = 0; i < equations.size(); i++) {
                        sum *= equations[i][index];
                        if (verbose) {
                            cout << equations[i][index];
                            if (i == equations.size() - 1) {
                                cout << " = " << sum << endl;
                            } else {
                                cout << " * ";
                            }
                        }
                    }
                    grand_total += sum;
                    index++;
                }
            }
            lineCount++;
        }
    }
    Input.close();
    cout << "Result: " << grand_total << endl;
    assert_equal(expected, grand_total);
}

int main() {
    task1("06-sample", 4277556, 3, true);
    task1("06", 4364617236318, 4, false);
    return 0;
}