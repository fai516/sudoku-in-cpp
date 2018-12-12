#include <string>
#include <vector>
#include "./typedef.h"

class Sudoku{
  uint base;
  uint dimension;
  uint length;
  vUint squares;
public:
  Sudoku();
  Sudoku(uint x);
  ~Sudoku();
  void setPuzzle(std::string input);
  void printConfig();
  void printSquares();
  void printTemplate();
  void generate();
  bool isValid();
};