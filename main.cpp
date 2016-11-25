#include <cstdlib>
#include <cstring>
#include <iostream>
#include "Board.h"
#include "NQueens.h"
#include "gettime.h"


int main(int argc, char *argv[]) {
  int size;
  int flag;
  long t1, t2;
  double elapsed;
  if (argc < 2) {
    std::cout << "USAGE: ./nqueens [-s|-p|-o1|-o2] <size>" << std::endl;
    return 1;
  }

  size = atoi(argv[argc-1]);

  if (argc >= 3 && (strcmp(argv[1], "-p") == 0 || strcmp(argv[1], "--parallel") == 0)) {
    flag = PARALLEL;
  } else if(argc >= 3 && (strcmp(argv[1], "-o1") == 0 || strcmp(argv[1], "--optimize1") == 0)) {
    flag = OPT1;
  } else if(argc >= 3 && (strcmp(argv[1], "-o2") == 0 || strcmp(argv[1], "--optimize2") == 0)) {
    flag = OPT2;
  } else {
    flag = SERIAL;
  }

  Board board = Board(size);
  std::cout << "optimization level = " << flag << std::endl;
  
  std::cout << "Created a board and now calculating number of solutions..." << std::endl;
  t1 = util_gettime();
  std::cout << "There are " << solve(board, flag) << " solutions to N-Queens for n = " << size << "." << std::endl;
  t2 = util_gettime();
  elapsed = (t2-t1)/(1000.f);
  std::cout << "Total elapsed time: " << elapsed << " seconds" << std::endl;

  return 0;
}
