# 8-puzzle-solver

A C++ implementation to solve the classic 8-puzzle game using
  1. The standard A<sup>\*</sup> algorithm using Tile Mismatch Count and Manhattan Distance heuristics.
  2. A modified version of A<sup>\*</sup> in which a node is expanded to a given fixed depth using BFS strategy. After expansion, nodes are added in the usual A<sup>\*</sup> order.
  
Both implementations are compared on the basis of max. fringe length and no. of expanded nodes.

## Instructions to Run

Option 1: Run the shell script 8Puzzle.sh
```bash
./8Puzzle.sh
```

Option 2: Open Terminal and issue following commands:
```bash
g++ 8Puzzle.cpp -o 8Puzzle
./8Puzzle
```

## Note

While generating random initial states, some states generated are invalid. They are not solvable. To generate a random set of valid initial states, uncomment lines 253, 254, 257, 258 and comment lines 260-262 (Given in Comments) in the file 8Puzzle.cpp.
