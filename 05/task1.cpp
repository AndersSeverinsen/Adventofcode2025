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

bool inRanges(vector<tuple<long long, long long>> ranges, long long id) {
    for (tuple<long long, long long> range : ranges) {
        long long start = get<0>(range);
        long long stop = get<1>(range);
        if (id >= start && id <= stop) {
            return true;
        }
    }
    return false;
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
    vector<tuple<long long, long long>> ranges;
    bool isRanges = true;
    long long fresh_ids = 0;
    while (getline (Input, line)) {
        if (line == "") {
            isRanges = false;
            if (verbose) {
                cout << endl;
            }
        } else if (isRanges) {
            long long start = 0;
            long long stop = 0;
            bool startNumber = true;
            for (char c : line) {
                if (c == '-') {
                    startNumber = false;
                } else if (startNumber) {
                    start *= 10;
                    start += (int)c - 48;
                } else {
                    stop *= 10;
                    stop += (int)c - 48;
                }
            }
            tuple<long long, long long> range = make_tuple(start, stop);
            ranges.push_back(range);
            if (verbose) {
                cout << start << "-" << stop << endl;
            }
        } else {
            long long id = stoll(line);
            if (verbose) {
                cout << id << endl;
            }
            if (inRanges(ranges, id)) {
                fresh_ids++;
            }
        }
    }
    Input.close();
    cout << "Result: " << fresh_ids << endl;
    assert_equal(expected, fresh_ids);
}

int main() {
    task1("05-sample", 3, true);
    task1("05", 517, false);
    return 0;
}