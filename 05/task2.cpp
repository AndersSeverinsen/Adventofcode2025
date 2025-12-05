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
    vector<tuple<long long, long long>> ranges;
    long long fresh_ids = 0;
    while (getline (Input, line)) {
        if (line == "") {
            if (verbose) {
                cout << endl;
            }
            break;
        } else {
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
        }
    }
    Input.close();

    bool overlap = true;
    while (overlap) {
        vector<tuple<long long, long long>> nranges;
        int start_size = ranges.size();
        for (int i = 0; i < ranges.size(); i++) {
            tuple<long long, long long> range = ranges[i];
            long long start = get<0>(range);
            long long stop = get<1>(range);

            if (nranges.empty()) {
                nranges.push_back(range);
                continue;
            }
            bool addedOrExists = false;
            for (int j = 0; j < nranges.size(); j++) {
                tuple<long long, long long> nrange = nranges[j];
                long long nstart = get<0>(nrange);
                long long nstop = get<1>(nrange);

                if (stop == nstop && start == nstart) {
                    addedOrExists = true;
                    continue;
                } else if (nstop <= stop && nstart <= start && nstop >= start) {
                    tuple<long long, long long> nnrange = make_tuple(nstart, stop);
                    nranges[j] = nnrange;
                    addedOrExists = true;
                    break;
                } else if (start <= nstart && stop <= nstop && nstart <= stop) {
                    tuple<long long, long long> nnrange = make_tuple(start, nstop);
                    nranges[j] = nnrange;
                    addedOrExists = true;
                    break;
                } else if (nstart <= start && nstop >= stop) {
                    addedOrExists = true;
                    break;
                } else if (nstart >= start && nstop <= stop) {
                    tuple<long long, long long> nnrange = make_tuple(start, stop);
                    nranges[j] = nnrange;
                    addedOrExists = true;
                    break;
                }
            }
            if (!addedOrExists) {
                nranges.push_back(range);
            }
        }
        if (verbose) {
            for (tuple<long long, long long> nrange : nranges) {
                long long nstart = get<0>(nrange);
                long long nstop = get<1>(nrange);
                cout << nstart << "-" << nstop << endl;
            }
            cout << endl;
        }
        ranges = nranges;

        if (ranges.size() == start_size) {
            overlap = false;
        }
    }
    for (tuple<long long, long long> range : ranges) {
        long long start = get<0>(range);
        long long stop = get<1>(range);
        fresh_ids += stop - start + 1;
    }
    cout << "Result: " << fresh_ids << endl;
    assert_equal(expected, fresh_ids);
}

int main() {
    task2("05-sample", 14, true);
    task2("05", 336173027056994, false);
    return 0;
}