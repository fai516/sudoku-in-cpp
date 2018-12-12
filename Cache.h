#include "./typedef.h"
#include <set>
#include <vector>
using namespace std;
struct Cache{
  uint b;
  uint d;
  vector< set<uint> > collection;
  Cache();
  Cache(uint x);
  uint randomDraw(uint index);
  void removeSetElem(uint index,uint value);
};