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

tuple<int, int> findS(vector<string> map) {
    for (int y = 0; y < map.size(); y++) {
        for (int x = 0; x < map[y].length(); x++) {
            if (map[y][x] == 'S') {
                tuple<int, int> coord = make_tuple(x, y);
                return coord;
            }
        }
    }
    cerr << "No 'S' found in the input." << endl;
    throw std::exception();
}

void moveTachyonBeamDown(vector<string> *map, tuple<int, int> coord, long long *splits) {
    int x = get<0>(coord);
    int y = get<1>(coord);

    if (y >= (*map).size()) { return; }

    if ((*map)[y+1][x] == '.') {
        (*map)[y+1][x] = '|';
        tuple<int, int> ncoord = make_tuple(x, y+1);
        moveTachyonBeamDown(map, ncoord, splits);
    } else if ((*map)[y+1][x] == '^') {
        (*splits)++;
        if (x-1 >= 0) {
            tuple<int, int> ncoord = make_tuple(x-1, y);
            moveTachyonBeamDown(map, ncoord, splits);
        }
        if (x+1 < (*map)[y+1].length()) {
            tuple<int, int> ncoord = make_tuple(x+1, y);
            moveTachyonBeamDown(map, ncoord, splits);
        }
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
    tuple<int, int> sLocation = findS(map);
    long long splits = 0;
    moveTachyonBeamDown(&map, sLocation, &splits);
    if (verbose) {
        for (string s : map) {
            cout << s << endl;
        }
    }
    cout << "Result: " << splits << endl;
    assert_equal(expected, splits);
}

int main() {
    task1("07-sample", 21, true);
    task1("07", 1555, false);
    return 0;
}