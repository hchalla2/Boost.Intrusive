#define BOOST_TEST_MODULE example
#include <boost/test/included/unit_test.hpp>
#include "seg_tree.hpp"
BOOST_AUTO_TEST_CASE( Iterator_test )
{
  //Declaring and initialising the input array.
  int inputarr[100];
  int i;
  for(i=0;i<100;i++)
    inputarr[i]=1;
  //Declaring and building segment tree
  segment_tree<int> Newtree;
  Newtree.seg_build(0,99,inputarr,100,sum);
  //Declaring the Iterator
  segment_tree<int>::Iterator itr;
  //Begin function is called which returns NULL if no node is present else returns pointer to first node i.e root.
  itr.fex=Newtree.begin();
  int temp=0;
  if(itr.fex==NULL && Newtree.no_nodes==0)
  {
    temp=1;
  }
  else if(itr.fex!=NULL && Newtree.no_nodes>0)
  {
    temp=1;
  }
  BOOST_CHECK_EQUAL(temp,1);
  //get_parent is called which returns 0 if input Iterator points to root else returns 0
  node<int> *parent=Newtree.get_parent(itr.fex);
  temp=0;
  if(parent==itr.fex && parent->index==0)//checks whether node which iterator points is root or not
  {
    temp=1;
  }
  if(parent!=itr.fex && itr.fex->index!=0)
  {
    temp=1;
  }
  BOOST_CHECK_EQUAL(temp,1);
  //get_left_child is called which returns 0 if input iterator is leaf node else returns 1
  node<int> *left_child=Newtree.get_left_child(itr.fex);
  temp=0;
  if(left_child==itr.fex && left_child->start==left_child->end)//checks whether node which iterator points is leaf node or not
  {
    temp=1;
  }
  if(left_child!=itr.fex && itr.fex->start!=itr.fex->end)
  {
    temp=1;
  }
  BOOST_CHECK_EQUAL(temp,1);
  //get_right_child is called which returns 0 if input iterator is leaf node else returns 1
  node<int> *right_child=Newtree.get_right_child(itr.fex);
  temp=0;
  if(right_child==itr.fex && right_child->start==right_child->end)//checks whether node which iterator points is leaf node or not
  {
    temp=1;
  }
  if(right_child!=itr.fex && itr.fex->start!=itr.fex->end)
  {
    temp=1;
  }
  BOOST_CHECK_EQUAL(temp,1);




}
