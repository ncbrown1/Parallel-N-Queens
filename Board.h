#ifndef NQUEENS_BOARD_H
#define NQUEENS_BOARD_H

#include <cstddef>

class Board {
public:
	const size_t size;

	Board(size_t size);
	virtual ~Board();
  Board(const Board &other);
	void add_queen(int row, int column);
	void remove_queen(int row, int column);
	int queens_in_row(int row);
	int queens_in_column(int column);
	int queens_in_ldiagonal(int row, int column);
	int queens_in_rdiagonal(int row, int column);
	bool queen_at(int row, int column);
	void init_permutation(const int permutation_index);
  bool validate_queen(int row, int column);
  bool validate_nqueens(int offset);
  bool validate_nqueens();

private:
	int reflect(int col);
	int *queens;
};

class Column {
public:
	Column *prev; // the solution up to this column
	int value;
	Column(Column *prev, int value) : prev(prev), value(value) {}
};

class CBoard {
public:
	const size_t size;

	CBoard(size_t size);
	CBoard(Board b);
	virtual ~CBoard();
	CBoard(const CBoard &other);

	Column *get(int index);
	bool is_complete();
	bool add_queen(int row);
	bool remove_queen();
private:
	int last_index;
	Column *last;
};

#endif
