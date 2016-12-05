#include "Board.h"
#include <vector>
#include "Tree.h"

#define SERIAL 0
#define PARALLEL 1
#define OPT1 2
#define OPT2 3

bool place_queen(Board &board, int row, int column);

int solve_serial(Board &board, int column);
int solve_parallel(Board board, int column);
int solve_opt1(Board &board, int column);
int solve_opt2(Board &board, int column);

void dfs_permute(int *numbers, int size, const Tree *tree, int length, std::vector<bool> visited);

int solve(Board &board, int flag);
