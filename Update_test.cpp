#define BOOST_TEST_MODULE example
#include <boost/test/included/unit_test.hpp>
#include "seg_tree.hpp"
/*
This function builds segment tree and updates index and tree and check whether the
updated tree holds correct values or not in the nodes.Here the data-type considered is 'int'
*/
int update_int_check_sum(int ss,int se,int size,int *inputarr,int ind,int val)
{
  //Building the segment tree
  segment_tree<int> Newtree;
  Newtree.seg_build(ss,se,inputarr,size,sum);
  //updating the input array.
  inputarr[ind]=val;
  int no_nodes=Newtree.no_nodes;
  int i;
  //Updating the segment tree
  Newtree.segtree_update(0,99,ind,inputarr,sum);
  for(i=0;i<no_nodes;i++)
  {
    int origvalue=0;
    if(Newtree.segtree_node[i].start!=Newtree.segtree_node[i].end)
    {
      //calculates the value that should be present in node using the brute-force approach.
      for(int m=Newtree.segtree_node[i].start;m<=Newtree.segtree_node[i].end;m++)
      {
        origvalue+=inputarr[m];
      }
      //This compares values calculated from 2 approaches i.e segment tree and brute-force approaches.
      BOOST_CHECK_EQUAL(origvalue,Newtree.segtree_node[i].value);
    }
  }
  return 1;
}
/*
This function builds segment tree and updates index and tree and check whether the
updated tree holds correct values or not in the nodes.Here the data-type considered is 'Point'
*/
int update_int_check_sum(int ss,int se,int size,Point *input_point_arr,int ind,Point val)
{
  //Building the segment tree
  segment_tree<Point> Newtree;
  Newtree.seg_build(ss,se,input_point_arr,size,twosum);
  //updating the input array.
  input_point_arr[ind]=val;
  int no_nodes=Newtree.no_nodes;
  int i;
  //Updating the segment tree
  Newtree.segtree_update(ss,se,ind,input_point_arr,twosum);
  for(i=0;i<no_nodes;i++)
  {
    int origvalue_x=0,origvalue_y=0;
    if(Newtree.segtree_node[i].start!=Newtree.segtree_node[i].end)
    {
      //calculates the value that should be present in node using the brute-force approach.
      for(int m=Newtree.segtree_node[i].start;m<=Newtree.segtree_node[i].end;m++)
      {
        origvalue_x+=input_point_arr[m].x;
        origvalue_y+=input_point_arr[m].y;
      }
      //This compares values calculated from 2 approaches i.e segment tree and brute-force approaches.
      BOOST_CHECK_EQUAL(origvalue_x,Newtree.segtree_node[i].value.x);
      BOOST_CHECK_EQUAL(origvalue_y,Newtree.segtree_node[i].value.y);
    }
  }
  return 1;
}

BOOST_AUTO_TEST_CASE( update_test )
{
  int *inputarr;
  int i,temp,size=100;
  //Creates input array with data-type 'int'.
  for(i=0;i<size;i++)
  {
    inputarr=(int*)malloc(size*sizeof(int));
  }
  //Assigns values to input array
  for(i=0;i<size;i++)
  {
    inputarr[i]=1;
  }
  //Builds segment tree with 'int' input array of size=100 and (start,end=0,99) updating the index=1 with val=2
  update_int_check_sum(0,99,size,inputarr,1,2);
  //Builds segment tree with 'int' input array of size=100 and (start,end=0,99) updating the index=3 with val=2
  update_int_check_sum(0,99,size,inputarr,3,2);
  //Builds segment tree with 'int' input array of size=100 and (start,end=0,99) updating the index=5 with val=2
  update_int_check_sum(0,99,size,inputarr,5,2);
  //Builds segment tree with 'int' input array of size=100 and (start,end=0,99) updating the index=7 with val=2
  update_int_check_sum(0,99,size,inputarr,7,2);

  Point *input_point_arr;
  //Creates input array with data-type 'Point'.
  for(i=0;i<size;i++)
  {
    input_point_arr=(Point*)malloc(size*sizeof(Point));
  }
  //Assigns values to input array
  for(i=0;i<size;i++)
  {
    input_point_arr[i].x=1;
    input_point_arr[i].y=1;
  }
  Point first;
  first.x=4;
  first.y=5;
  //Builds segment tree with 'int' input array of size=100 and (start,end=0,99) updating the index=1 with new first
  update_int_check_sum(0,99,100,input_point_arr,3,first);
  first.x=6;
  first.y=7;
  //Builds segment tree with 'int' input array of size=100 and (start,end=0,99) updating the index=1 with new first
  update_int_check_sum(0,99,100,input_point_arr,4,first);
  first.x=1;
  first.y=10;
  //Builds segment tree with 'int' input array of size=100 and (start,end=0,99) updating the index=1 with new first
  update_int_check_sum(0,99,100,input_point_arr,10,first);
  first.x=100;
  first.y=2000;
  //Builds segment tree with 'int' input array of size=100 and (start,end=0,99) updating the index=1 with new first
  update_int_check_sum(0,99,100,input_point_arr,95,first);
}
