#include "Board.h"

#define MIN(x, y) (x) < (y) ? (x) : (y)

Board::Board(size_t size) : size(size) {
	queens = new int[size];
	for (size_t i = 0; i < size; ++i) {
		queens[i] = -1;
	}
}

Board::~Board() {
	delete[] queens;
}

void Board::add_queen(int row, int column) {
	queens[column] = row;
}

void Board::remove_queen(int row, int column) {
	queens[column] = -1;
}

bool Board::queen_at(int row, int column) {
	return queens[column] == row;
}

int Board::queens_in_row(int row) {
	int count = 0;
	for (size_t col = 0; col < size; ++col) {
		count = queens[col] == row ? count + 1 : count;
	}
	return count;
}

int Board::queens_in_column(int column) {
	return queens[column] != -1 ? 1 : 0;
}

int Board::queens_in_ldiagonal(int row, int column) {
	int left_diag_count = 0;
	int min = MIN(row, column);
	int cur_row = row - min;
	int cur_column = column - min;

	for (; cur_column < size && cur_row < size; ++cur_column, ++cur_row) {
		left_diag_count = queen_at(cur_row, cur_column)
														? left_diag_count + 1
														: left_diag_count;
	}

	return left_diag_count;
}

int Board::reflect(int col) {
	return size - 1 - col;
}

int Board::queens_in_rdiagonal(int row, int column) {
	int right_diag_count = 0;
	int min = MIN(row, reflect(column));
	int cur_row = row - min;
	int cur_column = reflect(column) - min;

	for (; cur_column < size && cur_row < size; ++cur_column, ++cur_row) {
		right_diag_count = queen_at(cur_row, reflect(cur_column))
														? right_diag_count + 1
														: right_diag_count;
	}


	return right_diag_count;
}
