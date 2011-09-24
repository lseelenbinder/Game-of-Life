#include <iostream>
#include <list>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "grid.h"
#include "board.h"

using namespace std;

void printBoolArray(bool* bA) {
    for (bool* i = bA; i < bA + sizeof(bA); i += sizeof(bool)) {
        cout << *i << endl;
    }
}

void runGame(int m, int n, int k, bool printBorder) {
    cout << "Board size: " << m << " x " << n << endl;
    cout << "Generations: " << k << endl;

    //setup board
    Board b = Board(m, n);
    cout << endl << "Inital Board (Generation 1): " <<  endl;
    b.printBoard(printBorder);

    for (long i = 1; i < k; ++i) { // we already are at generation 1
        if (b.isEmpty()) {
            cout << "All cells are dead. Aborting..." << endl;
            break;
        }
        b.age();
        cout << endl <<  "Generation: " << i+1 << endl;
        b.printBoard(printBorder);
        //printBoolArray(b.representation());
    }
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
