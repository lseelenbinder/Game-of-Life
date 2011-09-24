#ifndef BOARD_H
#define BOARD_H
#include "grid.h"

class Board : public Grid<bool> {
    bool empty;
    public:
        Board(unsigned int m, unsigned int n);
        void printBorder(int n);
        void printBoard(bool);
        void randomizeBoard();
        void age();
        int numNeighbors(int m, int n);
        bool* representation();
        bool isEmpty();
};
#endif
