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

long long invalid_ranges(long long start, long long end, bool verbose = false) {
    long long sum = 0;
    for (long long i = start; i <= end; i++) {
        string id = to_string(i);
        if (id.size() % 2 == 0) { 
            if (id.substr(0, id.size()/2) == id.substr(id.size()/2, id.size())) {
                sum += i;
                if (verbose) {
                    cout << "Adding ID: " << i << endl;
                }
            }
        }
    }
    return sum;
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
    long long first_id = 0;
    long long last_id = 0;
    bool first = true;
    while (getline (Input, line)) {
        for (char c : line) {
            if (c == ',') {
                if (verbose) {
                    cout << first_id << "-" << last_id << endl;
                }
                sum += invalid_ranges(first_id, last_id, verbose);
                first_id = 0;
                last_id = 0;
                first = true;
            } else if (c == '-') {
                first = false;
            } else {
                if (first) {
                    first_id *= 10;
                    first_id += (int)c - 48;
                } else {
                    last_id *= 10;
                    last_id += (int)c - 48;
                }
            }
        }
    }
    if (verbose) {
        cout << first_id << "-" << last_id << endl;
    }
    sum += invalid_ranges(first_id, last_id, verbose);
    Input.close();
    cout << "Result: " << sum << endl;
    assert_equal(expected, sum);
}

int main() {
    task1("02-sample", 1227775554, true);
    task1("02", 18952700150, false);
    return 0;
}