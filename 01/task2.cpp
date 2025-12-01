#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <fstream>
#include <assert.h>
#include <string>

using namespace std;

void assert_equal(int expected, int actual) {
    if (expected != actual) {
        cerr << "Assert failed! Expected: " << expected << ", but got: " << actual << endl;
    }
}

void task2(string name, int expected) {
    cout << "Task 2" << endl;
    cout << "Input: " << name << endl;
    string fileame = name + ".txt";
    ifstream Input(fileame);
    if (!Input.is_open()) {
        cerr << "Error opening the file!";
        return;
    }
    string line;
    int dial = 50;
    int res = 0;
    while (getline (Input, line)) {
        if (line[0] == 'R') {
            int rotate = stoi(line.substr(1, line.size()));
            int old_dial = dial;
            res += rotate/100;
            dial = (dial + rotate) % 100;
            if (dial < 0) {dial = 100 + dial; }
            if (dial == 0) { 
                res++; 
            } else if (old_dial != 0 && old_dial > dial) { 
                res++; 
            }
        } else if (line[0] == 'L') {
            int rotate = stoi(line.substr(1, line.size()));
            int old_dial = dial;
            res += rotate/100;
            dial = (dial - rotate) % 100;
            if (dial < 0) {dial = 100 + dial; }
            if (dial == 0) { 
                res++; 
            } else if (old_dial != 0 && old_dial < dial) { 
                res++; 
            }
        }
    }
    Input.close();
    cout << "Result: " << res << endl;
    assert_equal(expected, res);
}

int main() {
    task2("01-sample", 6);
    task2("01", 6789);
    return 0;
}