# Sliding-Puzzle-Algorithm
### Version 1.0
## Description
This project is an implementation of a program to solve the N-puzzle game using the A* algorithm or one of its variants. The goal is to find a valid sequence of moves to bring the puzzle to its final state, also known as the "snail solution."
## Main Features

- Supports different puzzle sizes: 3x3, 4x4, 5x5, up to 7x7. Beyond these sizes, the computational power of conventional machines is insufficient, as a 7x7 puzzle already represents 3.0414×10^62 possible states.

- Solves puzzles either generated randomly or provided via input files.

- Combines ten heuristics, including the Manhattan distance.

- Displays statistics at the end of the search :
  - Total number of states selected.
  - Maximum number of states in memory.
  - Number of moves required to solve the puzzle.
  - Sequence of states leading to the solution.

- Handles unsolvable cases with an error message.
## Installation
Clone the repository:

```
git clone https://github.com/Maeltarh/Sliding-Puzzle-Algorithm.git
```
Navigate to the project directory:
```
cd Sliding-Puzzle-Algorithm
```
Compile the program:
```
make
```
A usage guide for the program is provided when executing the Makefile.

### Example of Input File
The input files must follow the format below:
```
# Puzzle size
3
# Puzzle grid (0 represents the empty space)
3 1 2
4 5 0
7 8 6
```
## Bonus
The project also includes implementations of uniform-cost search and greedy search. These algorithms are executed with the same heuristics but may produce different solutions.
