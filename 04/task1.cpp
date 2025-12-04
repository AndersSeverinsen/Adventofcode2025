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

bool lessThanFourAdjacent(int x, int y,vector<vector<char>> map) {
    int adjacent_rolls = 0;
    if (y > 0) {
        if (x > 0 && map[y-1][x-1] == '@') adjacent_rolls++;
        if (map[y-1][x] == '@') adjacent_rolls++;
        if (x < map[y-1].size()-1 && map[y-1][x+1] == '@') adjacent_rolls++;
    }
    
    if (x > 0 && map[y][x-1] == '@') adjacent_rolls++;
    if (x < map[y].size()-1 && map[y][x+1] == '@') adjacent_rolls++;

    if (y < map.size()-1) {
        if (x > 0 && map[y+1][x-1] == '@') adjacent_rolls++;
        if (map[y+1][x] == '@') adjacent_rolls++;
        if (x < map[y+1].size()-1 && map[y+1][x+1] == '@') adjacent_rolls++;
    }
    return adjacent_rolls < 4;
}

int forklift(vector<vector<char>> map, long long sum, bool verbose = false) {
    for (int y = 0; y < map.size(); y++) {
        for (int x = 0; x < map[y].size(); x++) {
            char c = map[y][x];
            if (c == '@') {
                if (lessThanFourAdjacent(x, y, map)) {
                    if (verbose) {
                        cout << "x";
                    }
                    sum++;
                } else {
                    if (verbose) {
                        cout << c;
                    }
                }
            } else {
                if (verbose) {
                    cout << c;
                }
            }
        }
        if (verbose) {
            cout << endl;
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
    vector<vector<char>> map;
    while (getline (Input, line)) {
        vector<char> ymap;
        for (char c : line) {
            if (verbose) {
                cout << c;
            }
            ymap.push_back(c);
        }
        if (verbose) {
            cout << endl;
        }
        map.push_back(ymap);
    }
    cout << endl;
    long long sum = 0;
    sum = forklift(map, sum, verbose);
    Input.close();
    cout << "Result: " << sum << endl;
    assert_equal(expected, sum);
}

int main() {
    task1("04-sample", 13, true);
    task1("04", 1508, false);
    return 0;
}