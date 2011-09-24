#ifndef GRID_H
#define GRID_H
#include <iostream>

template <typename Cell>
class Grid {
  Cell *grid;
  const unsigned int M, N;
public:
	class RowPtr {
		Cell *ptr;
		RowPtr(Cell *_ptr) : ptr(_ptr) { ; }
	public:
		friend class Grid<Cell>;
		RowPtr() : ptr(0) { ; }
		Cell &operator[](unsigned int col) { return ptr[col]; }
		const Cell &operator[](unsigned int col) const { return ptr[col]; }
	};

	class ConstRowPtr {
		const Cell *ptr;
		ConstRowPtr(const Cell *_ptr) : ptr(_ptr) { ; }
	public:
		friend class Grid<Cell>;
		ConstRowPtr() : ptr(0) { ; }
		const Cell &operator[](unsigned int col) const { return ptr[col]; }
	};
	
  Grid(unsigned int m, unsigned int n) : M(m), N(n) {
    grid = new Cell[M*N];
  }
  
  RowPtr operator[](unsigned int m) { return RowPtr(grid + m*N); }
  ConstRowPtr operator[](unsigned int m) const { return ConstRowPtr(grid + m*N); }
  
  unsigned int ColCount() const { return N; }
  unsigned int RowCount() const { return M; }
  

	void print(std::ostream &os) const {
		unsigned int r, c;
		
		for (r=0; r < M; ++r) {
			for (c=0; c < N; ++c) {
				os << (*this)[r][c] << ' ';
			}
			os << std::endl;
		}
	}
    void empty() {
        delete grid;
    }
};
#endif
