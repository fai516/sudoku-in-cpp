#include "./Cache.h"
#include "./Sudoku.h"
#include "./typedef.h"
#include "./utility.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
using namespace std;
Sudoku::Sudoku(){
  Sudoku(3);
}
Sudoku::Sudoku(uint x) : base(x),dimension(x*x),length(dimension*dimension){
  squares.resize(length,0);
}
void Sudoku::setPuzzle(string input){
  if(input.size()!=length)
    cout << "Input string has to be equal to " << length <<" and your input length is " << input.size() << endl;
  else{
    //taking every char from input string - covert them into integer and puting in squares vector
    transform(input.begin(),input.end(),squares.begin(),[](char ch){return ch-'0';});
  }
}
Sudoku::~Sudoku(){}
void Sudoku::printConfig(){
  cout << "base: " << base << endl
       << "dimension: " << dimension << endl
       << "length: " << length << endl;
}
void Sudoku::printSquares(){
  for(size_t i=0;i<length;i++){
    if(i%(dimension*base)==0&&i!=0){
      cout << endl;
      for(size_t j=0;j<(dimension+base-1);j++)
        cout << "-";
    } 
    if(i%dimension==0 && i!=0) cout << endl;
    if(i%base==0 && i!=0 && i%dimension!=0) cout << "|";
    if(squares[i]==0){
      cout << " ";
    }
    else{
      cout << squares[i];
    }
  }
  cout << endl;
}

void Sudoku::printTemplate(){
  for(size_t i=0;i<length;i++){
    if(i%(dimension*base)==0&&i!=0){
      cout << endl;
      for(size_t j=0;j<(3*dimension+base-1);j++)
        cout << "-";
    } 
    if(i%dimension==0 && i!=0) cout << endl;
    if(i%base==0 && i!=0 && i%dimension!=0) cout << "|";
    cout << setw(2) << i << " ";
  }
  cout << endl;
}
bool Sudoku::isValid(){
  string direction = "rcg";
  map<char,char> map = {{'r','c'},{'c','r'},{'g','g'}};
  for(auto ch:direction){
    string sMAP(1,map[ch]);
    vUint refs = indexGenerator(base,sMAP);
    for(auto ref:refs){
      string sCH(1,ch);
      vUint indexes = indexGenerator(base,sCH,ref);
      sUint set;
      for(auto index:indexes){
        if(set.end()!=set.find(squares[index]))
          return false;
        set.insert(squares[index]);
      }
    }
  }
  return true;
}
void Sudoku::generate(){
  bool isSolution = false;
  uint maxRun = 5000;
  vUint out(length);
  while(!isSolution&&maxRun--){
    Cache cache(base);
    for(size_t i=0;i<length;i++){
      //cout << "Attempt " << i << ": ";
      uint pick = cache.randomDraw(i);
      if(pick==0){break;}
      cache.removeSetElem(i,pick);
      out[i]=pick;
      if(i==length-1) isSolution=true;
    }
  }
  squares = out;
}