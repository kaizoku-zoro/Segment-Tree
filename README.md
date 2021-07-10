# Segment-Tree

Usage Instructions:

1. include the header file by writing #include "SegmentTree.h" at the top of your file.

2. Construct a seg tree by passing in to the constructor function:
  a vector (or an array and its size), its datatype, the function to be applied to your ranges, Identity value of the function.
3. Example usage:
  int small(int x,int y){return min(x,y);}
  SegmentTree < int > mySegTree(vector,INT_MAX,small);

  int sum(int x,int y){return x+y;}
  SegmentTree < int > mySegTree(vector,0,sum);

  long long product(long long x,long long y){return x*y;}
  SegmentTree < long long > mySegTree(vector,1,product);
