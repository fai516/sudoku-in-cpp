#include <functional>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include "./typedef.h"
#include "./utility.h"
using namespace std;

vUint indexGenerator(uint base, string types, uint pos, bool onlyGreater){
  uint d=base*base;
  vUint out;
  sUint set;
  function<uint()> aaa;
  auto addToSet = [](sUint& set,uint l,function<uint()> func){
    //unit l: length of output vector
    //declare temporary vector
    vUint tmp(l);
    generate(tmp.begin(),tmp.end(),func);
    set.insert(tmp.begin(),tmp.end());
    return tmp;
  };
  for(char& ch:types){
    if(pos==-1){
      switch(ch){
        case 'r':addToSet(set,d,[i=0]()mutable{return i++;});break;
        case 'c':addToSet(set,d,[i=0,d]()mutable{return d*i++;});break;
        case 'g':{
          vUint ref = addToSet(set,base,[base,d,i=0]()mutable{return d*base*i++;});
          for(auto n:ref) 
            addToSet(set,base,[base,n,i=0]()mutable{return n+base*i++;});
          break;
        }
        default: break;
      }
    }
    else{
      uint rowRef = pos/9;
      uint colRef = pos%9;
      uint gRowRef = rowRef/base*base;
      uint gColRef = colRef/base*base;
      switch(ch){
        case 'r':addToSet(set,d,[i=0,rowRef,d]()mutable{return d*rowRef+i++;});break;
        case 'c':addToSet(set,d,[i=0,colRef,d]()mutable{return (d*i++)+colRef;});break;
        case 'g':{
          vUint ref = addToSet(set,base,[i=0,d,gColRef,gRowRef]()mutable{return d*gRowRef+gColRef+i++;});
          for(auto n:ref)
            addToSet(set,base,[d,n,i=0]()mutable{return n+(d*i++);});
          break;
        }
        default:break;
      }
    }
  }
  if(onlyGreater){
    for(auto n:set){
      if(n>pos) out.push_back(n);
    }
  }
  else{
    copy(set.begin(),set.end(),back_inserter(out));
  }
  //for(auto n:out) cout << n << " ";
  return out;
}

ostream& operator<<(ostream& out,vUint in){
  out << "[";
  for(size_t i=0;i<in.size();i++){
    out << in[i];
    if(i!=in.size()-1) cout << ",";
  }
  out << "]";
  return out;
}