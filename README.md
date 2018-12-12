# Sudoku in C++
![alt text](https://www.cs.dartmouth.edu/~cbk/classes/10/16fall/notes/18/img/sudoku-soln.png)
This is a simple C++ program that can generate sudoku puzzle. The Puzzle is guaranteed valid. Newer language feature and syntax is used at this time.

## Usage
Use `make`
This program reqires C++14. Make sure your complier suport the latest C++ feature.
GCC: https://gcc.gnu.org/
Clang: https://clang.llvm.org/

## How the generator works
###Brute Force with "smart" back-tracking
Each square has its corresponding "set". Those sets tells the computer what numbers available for the square. 

For each square, the program will draw a number randomly from the set; then omit this number from the sets that in the same row, column, and grid. Therefore, as the program proceeding to each row, all the numbers in the sets should be minimized.

###Preventing deadlock
Sometime the generator might be in "deadlock" situation that the square has no possible number to put, since all other row/col/grid had been filled with 9 distinct numbers. In fact, the later square it generate, the higher chance to get "deadlock".
In order to solve it, there are two options:
The easier: Putting a infinite loop outside the square iterator, the for loop will breaks and run it again if and only if the deadlock was found. This method is easy but it is ralatively time-cosuming.

The faster: Making a memory map/queue to track down the selection made by the program. If deadlock was found, the program will go back to the previous square to seek the altherative solution. This would be more code to write, but it is faster.