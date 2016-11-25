#include "NQueens.h"

bool place_queen(Board &board, int row, int column) {
  board.add_queen(row, column);
  if (!board.validate_queen(row, column)) {
    board.remove_queen(row, column);
    return false;
  }
  return true;
}


int solve_serial(Board &board, int column) {
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
              : num_solutions + solve_serial(board, column + 1);

      // and remove the queen for next check
      board.remove_queen(i, column);
    }
  }

  return num_solutions;
}


int solve_parallel(Board &board, int column) {
  return 1;
}


int solve_opt1(Board &board, int column) {
  return 2;
}


int solve_opt2(Board &board, int column) {
  return 3;
}


int solve(Board &board, int flag) {
  switch(flag) {
    case PARALLEL:
      return solve_parallel(board, 0);
    case OPT1:
      return solve_opt1(board, 0);
    case OPT2:
      return solve_opt2(board, 0);
    case SERIAL: default:
      return solve_serial(board, 0);
  }
}
