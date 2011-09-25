#ifndef BOARD_H
#define BOARD_H
#include "grid.h"
#include <vector>

class Board : public Grid<bool> {
    bool emptyBoard;
    public:
        Board(unsigned int m, unsigned int n);
        void printBorder(int n);
        void printBoard(bool);
        void randomizeBoard();
        void age();
        int numNeighbors(int m, int n);
        std::vector<bool> representation();
        bool isEmpty();
        int size();
};
#endif
