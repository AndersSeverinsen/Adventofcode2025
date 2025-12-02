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
        bool added = false;
        for (int j = 2; j <= id.size(); j++) { 
            int jump = id.size() / j;
            if (id.size() % j == 0) {
                vector<string> id_vec;
                for (int k = 0; k < j; k++) {
                    string id_sub;
                    id_sub = id.substr(k*jump, jump);
                    id_vec.push_back(id_sub);
                }
                string pre = "";
                for (int k = 0; k < j; k++) {
                    if (k == 0) {
                        pre = id_vec[k];
                    } else if (k == j-1) {
                        if (pre != id_vec[k]) {
                            break;
                        } else {
                            sum += i;
                            if (verbose) {
                                cout << "Adding ID: " << i << endl;
                            }
                            added = true;
                            break;
                        }
                    } else {
                        if (pre != id_vec[k]) {
                            break;
                        }
                    }
                }
            }
            if (added) {
                break;
            }
        }
    }
    return sum;
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
    task2("02-sample", 4174379265, true);
    task2("02", 28858486244, false);
    return 0;
}