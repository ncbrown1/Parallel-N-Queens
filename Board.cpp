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

Board::Board(const Board &other) : size(other.size) {
  queens = new int[other.size];
  for (size_t i = 0; i < other.size; ++i) {
    queens[i] = other.queens[i];
  }
}


// Set board to be a permutation of integers 1 - N based on the perm_index
//
// This algorithm uses Lehmer codes to generate the perm-index-th permutation
// of the numbers 1-N.  See https://en.wikipedia.org/wiki/Lehmer_code and
// https://en.wikipedia.org/wiki/Factorial_number_system#Permutations for more
// information on permutations and factorial numbering

void Board::init_permutation(int perm_index) {
	// Compute the factorial form of the decimal number n
	// This gives us the so-called Lehmer code

	// Ensure queens are zero initialized
	for (int i = 0; i < size; ++i) {
		queens[i] = 0;
	}

	int last = perm_index;
	for (int i = 1; i <= size; ++i) {
		if (last == 0) { // break whenever last quotient is zero
			break;
		}
		queens[size - i] = last % i;
		last /= i;
	}

	// Convert the actual permutation from the Lehmer code
	for (int i = size - 1; i >= 0; --i) { // Beginning from right and move left
		for (int j = i + 1; j < size ; ++j) {
			if (queens[j] >= queens[i]) {
				// For all elements to the right of our position are greater/equal, increment them
				++queens[j];
			}
		}
	}
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

bool Board::validate_queen(int row, int column) {
  if (queens_in_row(row) > 1
      || queens_in_column(column) > 1
      || queens_in_ldiagonal(row, column) > 1
      || queens_in_rdiagonal(row, column) > 1) {
    return false;
  }
  return true;
}

bool Board::validate_nqueens(int offset)  {
  int i;
  for(i=offset; i<size; i++) {
    if (!validate_queen(queens[i], i)) return false;
  }
  return true;
}

bool Board::validate_nqueens()  {
  return validate_nqueens(0);
}


CBoard::CBoard(size_t size) : size(size), last_index(-1), last(NULL) {}
CBoard::CBoard(Board b) : size(b.size), last_index(-1), last(NULL) {}
CBoard::~CBoard() {
	Column *tmp;
	while (last != NULL) {
		tmp = last->prev;
		delete last;
		last = tmp;
	}
	last = NULL;
}
CBoard::CBoard(const CBoard &other)
	: size(other.size), last_index(other.last_index), last(other.last) {}

Column * CBoard::get(int index) {
	Column * tmp = last;
	int i = last_index;
	if (index < 0 || index >= last_index)
		return NULL;
	while (i != index && tmp != NULL) {
		tmp = tmp->prev;
		i--;
	}
	return tmp;
}

bool CBoard::is_complete() {
	return last_index == size-1;
}

bool add_queen(int row) {
	if (is_complete() || row > size) return false;
	Column *tmp = last;
	int back_n = 1;
	while (tmp != NULL) {
		if (tmp->value == row || // if in same row
			tmp->value - back_n == row || // if in left diag
			tmp->value + back_n == row )  { // if in right diag
			return false; // invalid queen
		}
		tmp = tmp->prev;
		back_n += 1;
	}
	Column * col = new Column(last, row);
	last = col;
	last_index += 1;
	return true;
}

bool remove_queen() {
	if (last == NULL) return false;
	last_index -= 1;
	Column * tmp = last->prev;
	delete last;
	last = tmp;
}
