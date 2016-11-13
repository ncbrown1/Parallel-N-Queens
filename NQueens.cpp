#include "NQueens.h"

bool place_queen(Board &board, int row, int column) {
  board.add_queen(row, column);
  if (board.queens_in_row(row) > 1
      || board.queens_in_column(column) > 1
      || board.queens_in_ldiagonal(row, column) > 1
      || board.queens_in_rdiagonal(row, column) > 1) {
    board.remove_queen(row, column);
    return false;
  }
  return true;
}

int solve(Board &board, int column) {
  int i;
  int num_solutions = 0;

  // for each possible queen placement
  for (i = 0; i < board.size; i++) {
    if (place_queen(board, i, column)) { // if it is a valid move, we place it

      num_solutions =
          column == board.size - 1
              // if we are at the end, mark as solution
              ? num_solutions + 1
              // if more columns, recursively add next columns solution
              : num_solutions + solve(board, column + 1);

      // and remove the queen for next check
      board.remove_queen(i, column);
    }
  }

  return num_solutions;
}

int solve(Board &board) {
  return solve(board, 0);
}
