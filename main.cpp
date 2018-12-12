#include <algorithm>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include "./Sudoku.h"
#include "./typedef.h"
#include "./utility.h"
using namespace std;
using HDclock = chrono::high_resolution_clock;
using millisecond = chrono::duration<float,milli>;

string exampleInput(){
  return "572943168861527439934186527128435976743619285695278341219764853486351792357892614";
}


int main(){
  Sudoku* sudoku = new Sudoku(3);
  sudoku->setPuzzle(exampleInput());

  auto start = HDclock::now();
  sudoku->generate();
  auto end = HDclock::now();
  
  sudoku->printSquares();
  cout <<sudoku->isValid() << endl;
  millisecond elapsed_seconds(end-start);
  cout << elapsed_seconds.count() << "ms" << endl;
  delete sudoku;
  return 0;
}