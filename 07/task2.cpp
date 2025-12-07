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
        throw exception();
    }
}

long long calculateTimelines(vector<string> *map, bool verbose = false) {
    vector<long long> timelines((*map)[0].size(), 0);
    for (int y = 0; y < (*map).size(); y++) {
        vector<long long> ntimelines((*map)[y].size(), 0);
        for (int x = 0; x < (*map)[y].size(); x++) {
            if (y == 0) {
                if ((*map)[y][x] == 'S') {
                    ntimelines[x] = 1;
                }
            } else {
                if (((*map)[y-1][x] == 'S' || (*map)[y-1][x] == '|') && (*map)[y][x] == '.') {
                    (*map)[y][x] = '|';
                    ntimelines[x] += timelines[x];
                } else if ((*map)[y][x] == '^' && (*map)[y-1][x] == '|') {
                    (*map)[y][x-1] = '|';
                    if (ntimelines[x-1] == 0) {
                        ntimelines[x-1] = timelines[x-1];
                    }
                    ntimelines[x-1] += timelines[x];
                    (*map)[y][x+1] = '|';
                    if (ntimelines[x+1] == 0) {
                        ntimelines[x+1] = timelines[x+1];
                    }
                    ntimelines[x+1] += timelines[x];
                }
            }
        }
        timelines = ntimelines;
        if (verbose) {
            for (long long n : ntimelines) {
                cout << n << " ";
            }
            cout << endl;
        }
    }
    long long res = 0;
    for (long long t : timelines) {
        res += t;
    }
    return res;
}

void task2(string name, long long expected, bool verbose = false) {
    cout << "Task 2" << endl;
    cout << "Input: " << name << endl;
    string fileame = name + ".txt";
    ifstream Input(fileame);
    if (!Input.is_open()) {
        cerr << "Error opening the file!";
        return;
    }
    string line;
    vector<string> map;
    while (getline (Input, line)) {
        if (line != "") {
            map.push_back(line);
            if (verbose) {
                cout << line << endl;
            }
        }
    }
    Input.close();
    long long timelines = calculateTimelines(&map, verbose);
    if (verbose) {
        for (string s : map) {
            cout << s << endl;
        }
    }
    cout << "Result: " << timelines << endl;
    assert_equal(expected, timelines);
}

int main() {
    task2("07-sample", 40, true);
    task2("07", 12895232295789, false);
    return 0;
}