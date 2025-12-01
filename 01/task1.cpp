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

void task1(string name, int expected) {
    cout << "Task 1" << endl;
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
            dial = (dial + rotate) % 100;
            if (dial == 0) { res++; }
        } else if (line[0] == 'L') {
            int rotate = stoi(line.substr(1, line.size()));
            dial = (dial - rotate) % 100;
            if (dial == 0) { res++; }
        }
    }
    Input.close();
    cout << "Result: " << res << endl;
    assert_equal(expected, res);
}

int main() {
    task1("01-sample", 3);
    task1("01", 1147);
    return 0;
}