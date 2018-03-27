#define BOOST_TEST_MODULE example
#include <boost/test/included/unit_test.hpp>
#include "seg_tree.hpp"
/*
This function returns whether a segment tree can be built using the input argumens
and sum as merging function and the data-type stored is 'int'
*/
int check_build_int_sum(int ss,int se,int size)
{
  int *inputarr;
  int i,temp;
  //Declaring input array and initialising it.
  inputarr=(int*)malloc(size*sizeof(int));
  for(i=0;i<size;i++)
  {
    inputarr[i]=1;
  }
  //Building the segment tree using input array and merging function
  segment_tree<int> Newtree;
  temp=Newtree.seg_build(ss,se,inputarr,size,sum);
  return temp;
}
/*
This function checks all the nodes of the built segment tree whether the value stored is correct or not.
This function takes 'sum' as merging function
*/
int check_build_int_sum_values(int ss,int se,int size)
{
  int *inputarr,*prefix_inputarr;
  int i,temp;
  //Declaring input array and initialising it.
  for(i=0;i<size;i++)
  {
    inputarr=(int*)malloc(size*sizeof(int));
    prefix_inputarr=(int*)malloc(size*sizeof(int));
  }
  for(i=0;i<size;i++)
  {
    inputarr[i]=1;
  }
  //Building the prefix sum array.
  prefix_inputarr[0]=inputarr[0];
  for(i=1;i<size;i++)
  {
    prefix_inputarr[i]=prefix_inputarr[i-1]+inputarr[i];
  }
  //Building the segment tree using input array and merging function
  segment_tree<int> Newtree;
  temp=Newtree.seg_build(ss,se,inputarr,size,sum);
  int no_nodes=Newtree.no_nodes;
  for(i=0;i<no_nodes;i++)
  {
    int origvalue=0;
    if(Newtree.segtree_node[i].start!=Newtree.segtree_node[i].end) //Calculates the value over the range using a different approach which is assumed to be true
    {
      //Calculates the value over range using prefix sum array.
      if(Newtree.segtree_node[i].start==0)
      {
        origvalue=prefix_inputarr[Newtree.segtree_node[i].end];
      }
      else
      {
        origvalue=prefix_inputarr[Newtree.segtree_node[i].end]-prefix_inputarr[Newtree.segtree_node[i].start-1];
      }
      //Compares the values obtained from 2 different approaches i.e segment tree and prefix sum array.
    BOOST_CHECK_EQUAL(origvalue,Newtree.segtree_node[i].value);
    }
  }
  return temp;

}


BOOST_AUTO_TEST_CASE( build_update_test )
{
  int temp;

  //This checks the first condition in the seg_build function
  temp=check_build_int_sum(100,99,100);
  BOOST_CHECK_EQUAL(temp,0);

  //This checks the second condition in the seg_build function
 temp=check_build_int_sum(0,100,50);
 BOOST_CHECK_EQUAL(temp,0);

  //This checks the third condition in the seg_build function
  temp=check_build_int_sum(-1,99,100);
  BOOST_CHECK_EQUAL(temp,0);

  //This function checks all the nodes of segment tree
  check_build_int_sum_values(0,99,100);


}
