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
	int array[size];
	int branch[size];
	bool visited[size];
	for (int i = 0; i < size; ++i) {
		array[i] = i;
		branch[i] = -1;
		visited[i] = false;
	}
	dfs_permute(array, size, branch, 0, visited);

  return nqueens_solutions.get_value();
}

int count = 0;
void dfs_permute(int *numbers, int size, int *branch, int length, bool *visited) {
	int *next_branch = new int[size];

	// Copy and init board layout for this path
	for (int i = 0; i < length; ++i) {
		next_branch[i] = branch[i];
	}
	for (int i = length; i < size; ++i) {
		next_branch[i] = -1;
	}

	Board board = Board(next_branch, size);

	// Don't continue down this path of permutations if there's a conflict
	// This can hugely reduce the problem search space
	if (!board.validate_nqueens()) {
		return;
	}

	if (length == size){
		++count;
	}

	for (int i = 0; i < size; i++) {
		// For all elements that haven't been used in permutation
		if (!visited[i]) {
			// Add to permutation
			next_branch[length] = numbers[i];
			visited[i] = true;
			// Permute remaining elements
			dfs_permute(numbers, size, next_branch, length+ 1, visited);
			visited[i] = false;
		}
	}
}


int solve_opt2(Board &board, int column) {
  return 3;
}


int solve(Board &board, int flag) {
  switch(flag) {
    case PARALLEL:
      return solve_parallel(board, 0);
    case OPT1:
      return solve_opt1(board.size);
    case OPT2:
      return solve_opt2(board, 0);
    case SERIAL: default:
      return solve_serial(board, 0);
  }
}
