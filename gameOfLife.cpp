#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <list>
#include <vector>
#include "grid.h"
#include "board.h"

using namespace std;

bool compareBoolVector(vector<bool> &a, vector<bool> &b) {
    int size = a.size();
    for (int i = 0; i < size; ++i) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

void runGame(const int m, const int n, const int k, const bool printBorder) {
    cout << "Board size: " << m << " x " << n << endl;
    cout << "Generations: " << k << endl;

    //setup board
    Board b = Board(m, n);

    //print initial board
    cout << endl << "Inital Board (Generation 1): " <<  endl;
    b.printBoard(printBorder);

    //initialize container to hold generations
    vector< vector<bool> > generations;
    generations.push_back(b.representation());

    for (long i = 1; i < k; ++i) { // i = 1 because we are already at generation 1
        //progress to next generation
        b.age();

        //check for empty grid
        if (b.isEmpty()) {
            cout << "All cells are dead. Aborting..." << endl;
            exit(0);
        }

        //check for previous matching generations
        vector<bool> g = b.representation();
        for (int j = generations.size()-1; j >= 0; --j) {
            if (compareBoolVector(g, generations.at(j))) {
                cout << "Encountered duplicate of generation #" << j+1 << ". Aborting..." << endl;
                exit(0);
            }
        }
        generations.push_back(g);

        cout << endl <<  "Generation: " << i+1 << endl;
        b.printBoard(printBorder);
    }
    b.empty();
}

void printUsage() {
    cout << "usage: gameOfLife [-m mSIZE] -n nSIZE -k GENERATIONS [--noborder]" << endl;
}

int main(int argc, char* argv[]) {
    list<char*> args;
    int m, n, k;
    m = n = k = 0;
    bool printBorders = true;

    for (int i = 1; i < argc; ++i) { // add args to queue
        args.push_back(argv[i]);
    }
    if (args.size() == 0) {
        printUsage();
        return 0;
    }

    list<char*>::iterator iter = args.begin();
    for (; iter != args.end(); ++iter) {// iterate through arguments and flags
        if (strcmp(*iter, "--help") == 0) {
            printUsage();
            return 0;
        }
        else if (strcmp(*iter, "-m") == 0) {
            ++iter; // go to the number
            m = atoi(*iter);
            if (!m) {
                cerr << "Invalid option for -m" << endl;
                printUsage();
                return 1;
            }
        }
        else if (strcmp(*iter, "-n") == 0) {
            ++iter; // go to the number
            n = atoi(*iter);
            if (!n) {
                cerr << "must specify non-zero value for -n" << endl;
                printUsage();
                return 1;
            }
        }
        else if (strcmp(*iter, "-k") == 0) {
            ++iter; // go to the number
            k = atoi(*iter);
            if (!k) {
                cerr << "must specify non-zero value for -k" << endl;
                printUsage();
                return 1;
            }
        }
        else if (strcmp(*iter, "--noborder") == 0) {
            printBorders = false;
        }
        else {
            cerr << *iter << " is an invalid option" << endl;
            printUsage();
            return 1;
        }
    }
    if (m == 0) m = n;
    if (n == 0) {
        cerr << "must specify non-zero value for n" << endl;
        return 1;
    }
    if (k == 0) {
        cerr << "must specify non-zero value for k" << endl;
        return 1;
    }
    runGame(m, n, k, printBorders);

    return 0;
}
