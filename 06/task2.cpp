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

int findStopIndex(string line, int index) {
    for (int i = index+1; i < line.length(); i++) {
        if (line[i] != ' ') {
            return i-2;
        }
    }
    return line.length()-1;
}

void task2(string name, long long expected, int numberOfLines, bool verbose = false) {
    cout << "Task 2" << endl;
    cout << "Input: " << name << endl;
    string fileame = name + ".txt";
    ifstream Input(fileame);
    if (!Input.is_open()) {
        cerr << "Error opening the file!";
        return;
    }
    string line;
    vector<string> equations;
    long long grand_total = 0;
    int lineCount = 0;
    while (getline (Input, line)) {
        if (numberOfLines > lineCount) {
            equations.push_back(line);
            lineCount++;
        } else {
            int startIndex = 0;
            int stopIndex = 0;
            if (verbose) {
                for (string s : equations) {
                    cout << s << endl;
                }
                cout << line << "(" << line.length() << ")" << endl;
            }
            for (int l = 0; l < line.length(); l++) {
                char c = line[l];
                if (c == '+') {
                    startIndex = l;
                    stopIndex = findStopIndex(line, l);
                    long long sum = 0;
                    for (int i = startIndex; i <= stopIndex; i++) {
                        int number = 0;
                        for (int j = 0; j < equations.size(); j++) {
                            char c = equations[j][i];
                            if (c != ' ') {
                                if (verbose) { cout << c; }
                                number *= 10;
                                number += (int)c - 48;
                            }
                        }
                        sum += number;
                        if (verbose) {
                            if (i == stopIndex) {
                                cout << " = " << sum << endl;
                            } else {
                                cout << " + ";
                            }
                        }
                    }
                    grand_total += sum;
                } else if (c == '*') {
                    startIndex = l;
                    stopIndex = findStopIndex(line, l);
                    long long sum = 1;
                    for (int i = startIndex; i <= stopIndex; i++) {
                        int number = 0;
                        for (int j = 0; j < equations.size(); j++) {
                            char c = equations[j][i];
                            if (c != ' ') {
                                if (verbose) { cout << c; }
                                number *= 10;
                                number += (int)c - 48;
                            }
                        }
                        sum *= number;
                        if (verbose) {
                            if (i == stopIndex) {
                                cout << " = " << sum << endl;
                            } else {
                                cout << " * ";
                            }
                        }
                    }
                    grand_total += sum;
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
    task2("06-sample", 3263827, 3, true);
    task2("06", 9077004354241, 4, false);
    return 0;
}