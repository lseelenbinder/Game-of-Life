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
    empty = true;
    for (unsigned int m = 0; m < RowCount(); ++m) {
        for (unsigned int n = 0; n < ColCount(); ++n) {
            (*this)[m][n] = (rand() & 1);
            if ((*this)[m][n]) empty = false;
        }
    }

}

void Board::age() {
    Grid<bool> next(RowCount(), ColCount()); // use this grid to prevent
                                             // overwriting as we check
                                             // for neighbors
    int neighbors = 0;
    //calculate next generation and place in b
    for (unsigned int m = 0; m < RowCount(); ++m) {
        for (unsigned int n = 0; n < ColCount(); ++n) {
            neighbors = numNeighbors(m, n);
            switch (neighbors) {
                case 2:
                case 3:
                    if (!(*this)[m][n] && neighbors == 3) {
                        next[m][n] = true;
                    }
                    break;
                default:
                    next[m][n] = false; // death
                    break;
            }
        }
    }
    // copy next to Board's grid
    // also check for empty board
    empty = true;
    for (unsigned int m = 0; m < RowCount(); ++m) {
        for (unsigned int n = 0; n < ColCount(); ++n) {
            (*this)[m][n] = next[m][n];
            if (next[m][n]) empty = false;
        }
    }
    next.empty(); // free memory from grid
}

int Board::numNeighbors(int m, int n) {
    int num = 0;
    for (int i = -1; i < 2; ++i) {
        if (m == 0 && i == -1) continue; //edge detect
        if (m == ColCount()-1 && i == 1) continue; //edge detect
        for (int k = -1; k < 2; ++k) {
            if (n == 0 && k == -1) continue; //edge detect
            if (n == RowCount()-1 && k == 1) continue; //edge detect
            if (m+i == m && n+k == n) continue; // don't count actual cell

            if ((*this)[m+i][n+k]) ++num; // increment as a neighbor
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

bool Board::isEmpty() { return empty; }
int Board::size() { return ColCount() * RowCount(); }
