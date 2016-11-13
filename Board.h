#ifndef NQUEENS_BOARD_H
#define NQUEENS_BOARD_H

#include <cstddef>

class Board {
public:
	Board(size_t size);
	virtual ~Board();
	void add_queen(int row, int column);
	int queens_in_row(int row);
	int queens_in_column(int column);
	int queens_in_ldiagonal(int row, int column);
	int queens_in_rdiagonal(int row, int column);
	bool queen_at(int row, int column);

private:
	int reflect(int col);
	int *queens;
	size_t n;
};

#endif