#include<bits/stdc++.h>
#include "seg_tree.hpp"
using namespace std;
int main()
{
  int inputarr[100],i;
  for(i=0;i<100;i++)
    inputarr[i]=1;

//Declaring the object
  segment_tree<int> Newtree;
//building the segment tree
  Newtree.seg_build(0,99,inputarr,100,sum);
//Updating the input array
  inputarr[30]=0;
//Updating the segment tree
  Newtree.segtree_update(0,99,30,inputarr,sum);
//Querying the tree in the interval (2,35)
  Newtree.segtree_query(0,99,2,35,0,inputarr,sum);
//The query result for the range (2,35)
  cout << Newtree.query_result << endl;

}
