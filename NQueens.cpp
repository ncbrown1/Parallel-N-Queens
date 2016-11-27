#include "NQueens.h"
#include <cilk/cilk.h>
#include <cilk/reducer_opadd.h>

// global solution count for parallel calls
cilk::reducer_opadd<double> nqueens_solutions(0);

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


int solve_parallel(Board board, int column) {
  int i;

  // if we got a solution
  if (column >= board.size) {
    *nqueens_solutions += 1;
    return nqueens_solutions.get_value();
  }

  // for each possible queen placement
  for (i = 0; i < board.size; i++) {
    if (place_queen(board, i, column)) { // if it is a valid move, we place it
      // check the rest of the board in parallel
      cilk_spawn solve_parallel(board, column+1);
      // and remove the queen for next check
      board.remove_queen(i, column);
    }
  }

  cilk_sync;
  return nqueens_solutions.get_value();
}


int solve_opt1(const size_t size) {
	// compute factorial(size)
	int factorial = 1;
	for (int i = 1; i <= size; ++i) {
		factorial *= i;
	}

	// Evaluate each board permutation in parallel
	cilk_for (int i = 0; i < factorial; ++i) {
		Board board = Board(size);
		board.init_permutation(i); // unique permutation for each worker

		// Test each queen placement on board to see if there are conflicts
		if (board.validate_nqueens()) { // TODO maybe change this to just manually check diagonals at some point
			*nqueens_solutions += 1;
		}
	}

  return nqueens_solutions.get_value();
}


int solve_opt2(Column *last, int column, size_t size) {
    int i, back_n;
    bool valid;
    Column *tmp;

    // if we got a solution
    if (column == size) {
        delete last;
        *nqueens_solutions += 1;
        return nqueens_solutions.get_value();
    }

    // for each possible queen placement
    for (i = 0; i < size; i++) {
        tmp = last;
        back_n = 1;
        valid = true;
        while (tmp != NULL) {
            if (tmp->value == i || // if in same row
                tmp->value - back_n == i || // if in left diag
                tmp->value + back_n == i )  { // if in right diag
                valid = false; // invalid queen
                break;
            }
            tmp = tmp->prev;
            back_n += 1;
        }
        if (valid) {
            // check the rest of the board in parallel
            cilk_spawn solve_opt2(new Column(last, i), column + 1, size);
        }
    }

    cilk_sync;
    if (last != NULL) delete last;
    return nqueens_solutions.get_value();
}


int solve(Board &board, int flag) {
  switch(flag) {
    case PARALLEL:
      return solve_parallel(board, 0);
    case OPT1:
      return solve_opt1(board.size);
    case OPT2:
      return solve_opt2(NULL, 0, board.size);
    case SERIAL: default:
      return solve_serial(board, 0);
  }
}
