#include "./typedef.h"
#include "./Cache.h"
#include "./utility.h"
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <set>
#include <vector>
using namespace std;

  Cache::Cache(){Cache(3);}
  Cache::Cache(uint x) : b(x), d(x*x){
    sUint set;
    vUint tmp(d);
    std::iota(tmp.begin(),tmp.end(),1);
    set.insert(tmp.begin(),tmp.end());
    for(size_t i=0;i<d*d;i++){
      collection.push_back(set);
    }
  }
  uint Cache::randomDraw(uint index){
    uint length = collection[index].size();
    if(length==0) return 0;
    random_device rd;
    mt19937 generator(rd());
    std::uniform_int_distribution<uint> unif(0, length-1);//range: [0,max]
    auto it = collection[index].begin();
    // /+unif(generator)
    uint k = unif(generator);
    advance(it,k);
    return *(it);
  }
  void Cache::removeSetElem(uint index,uint value){
    //cout << "removeSetElem(" << index << "," << value <<") base= " << b <<endl;
    vUint indexList = indexGenerator(b,"rcg",index,true);
    //cout << "Proceding index="<<indexList << endl;
    for(char ref:indexList){
      auto pos = collection[ref].find(value);
      if(pos!=collection[ref].end())
        collection[ref].erase(pos);
    }
  }