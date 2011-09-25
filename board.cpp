#include <iostream>
#include <stdlib.h>
#include <vector>
#include "grid.h"
#include "board.h"

using namespace std;

Board::Board(unsigned int m, unsigned int n) : Grid<bool>(m, n) {
    randomizeBoard();
}

void Board::printBorder(int n) {
    for (int i = 0; i <= n+1; ++i) {
        cout << "**";
    }
    cout << "*" << endl;
}

void Board::printBoard(bool border) {
    if (border) printBorder(ColCount());
    for (unsigned int m = 0; m < RowCount(); ++m) {
        if (border) cout << " * ";
        for (unsigned int n = 0; n < ColCount(); ++n) {
            cout << ((*this)[m][n] ? "X " : "  ");
        }
        if (border) cout << "*";
        cout << endl;
    }
    if (border) printBorder(ColCount());
}

void Board::randomizeBoard() {
    srand(time(NULL));
    emptyBoard = true;
    for (unsigned int m = 0; m < RowCount(); ++m) {
        for (unsigned int n = 0; n < ColCount(); ++n) {
            (*this)[m][n] = (rand() & 1);
            if ((*this)[m][n]) emptyBoard = false;
        }
    }

}

void Board::age() {
    //calculate next generation
    Grid<bool> next(RowCount(), ColCount());

    for (unsigned int m = 0; m < RowCount(); ++m) {
        for (unsigned int n = 0; n < ColCount(); ++n) {
            int neighbors = numNeighbors(m, n);
            bool cell = (bool) (*this)[m][n];

            if (
                (cell && (neighbors == 2 || neighbors == 3)) || // sustained
                (!cell && neighbors == 3) // birth
                ) {
                next[m][n] = true;
            } else { // death
                next[m][n] = false;
            }
        }
    }

    // copy next generation to Board's grid
    // also check for empty board
    emptyBoard = true;
    for (unsigned int m = 0; m < RowCount(); ++m) {
        for (unsigned int n = 0; n < ColCount(); ++n) {
            (*this)[m][n] = next[m][n];
            if (next[m][n]) emptyBoard = false;
        }
    }
    next.empty(); // free memory from grid
}

int Board::numNeighbors(const int m, const int n) {
    int num = 0;
    // cast to (int) to prevent comparison of int and unsigned int
    int stopM = (m == (int) RowCount()-1) ? m : (m + 1);
    int stopN = (n == (int) ColCount()-1) ? n : (n + 1);
    // ternary operator determines if m or n is on the edge
    for (int _m = (m ? (m - 1) : m); _m <= stopM; ++_m) {
        for (int _n = (n ? (n - 1) : n); _n <= stopN; ++_n) {
            if (_m == m && _n == n) continue; // skip actual cell
            if ((*this)[_m][_n]) ++num;
        }
    } 
    return num;

}

vector<bool> Board::representation() { // for keeping track of generations
    vector<bool> b;
    if (isEmpty()) {
        return b;
    }
    int i = 0;
    for (unsigned int m = 0; m < RowCount(); ++m) {
        for (unsigned int n = 0; n < ColCount(); ++n) {
            b.push_back((*this)[m][n]);
            ++i;
        }
    }
    return b;
}

bool Board::isEmpty() { return emptyBoard; }
int Board::size() { return ColCount() * RowCount(); }
