#include <cstdlib>
#include <iostream>
#include "Board.h"
#include "NQueens.h"


int main(int argc, char *argv[]) {
  int size;
  if (argc < 2) {
    std::cout << "USAGE: ./nqueens <size>" << std::endl;
    return 1;
  }

  size = atoi(argv[1]);
  Board board = Board(size);
  
  std::cout << "Created a board and now calculating number of solutions..." << std::endl;
  std::cout << "There are " << solve(board) << " solutions to N-Queens for n = " << size << "." << std::endl;

  return 0;
}
