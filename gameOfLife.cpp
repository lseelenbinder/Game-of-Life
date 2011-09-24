#include <iostream>
#include <stdlib.h>
#include <string>
#include "grid.h"
#include "board.h"

using namespace std;

void printBoolArray(bool* bA) {
    for (bool* i = bA; i < bA + sizeof(bA); i += sizeof(bool)) {
        cout << *i << endl;
    }
}

void runGame(int m, int n, int k) {
    cout << "Board size: " << m << " x " << n << endl;
    cout << "Generations: " << k << endl;

    //setup board
    Board b = Board(m, n);
    cout << endl << "Inital Board (Generation 1): " <<  endl;
    b.printBoard();

    for (long i = 1; i < k; ++i) { // we already are at generation 1
        if (b.isEmpty()) {
            cout << "All cells are dead. Aborting..." << endl;
            break;
        }
        b.age();
        cout << endl <<  "Generation: " << i+1 << endl;
        b.printBoard();
        //printBoolArray(b.representation());
    }
}

int main(int argc, char* argv[]) {
    int _m, _n, _k;

    switch (argc) {
        case 1:
            cout << "usage: gameOfLife [mSIZE] nSIZE GENERATIONS" << endl;
            break;
        case 2:
            cout << "must have at least 2 arguments" << endl;
            cout << "usage: gameOfLife [mSIZE] nSIZE GENERATIONS" << endl;
            break;
        case 3:
            _m = _n = atoi(argv[1]);
            _k = atoi(argv[2]);
            runGame(_m, _n, _k);
            break;
        case 4:
            _m = atoi(argv[1]);
            _n = atoi(argv[2]);
            _k = atoi(argv[3]);
            runGame(_m, _n, _k);
    }
    return 0;
}
