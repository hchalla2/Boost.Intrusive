#include<bits/stdc++.h>
using namespace std;
#define MAX_ARRAY_SIZE 100000
/*
This class denotes the data-type of single node in segment tree.It
stores the start ,end indexes and position of node in segment tree.
*/
template<typename T> //T is the input array data-type
class node{
public:
  int start,end,index;
  T value;
};
/*
This a new data-type defined with two integer attributes.
*/
class Point{
public:
  int x,y;
};
/*
This is merging function which takes two Point objects as input and adds the corresponding fields and returns final object
*/
auto twosum=[](auto a,auto b)
{
  Point c;
  c.x=a.x+b.x;
  c.y=a.y+b.y;
  return c;
};
/*
This is merging function which takes two simple data-type objects and adds them and returns the result.
*/
auto sum=[](auto a,auto b)
{
  return (a+b);
};
/*
The main segment tree class
*/

template<typename T> //T is the input array data-type
class segment_tree
{

public:
  node<T>* segtree_node;
  int input_array_size;
  int no_nodes;
  T query_result;
public:
  //This constructor allocates memory for '3n' objects of type 'node<T>'
  segment_tree()
  {
    segtree_node=NULL;
    input_array_size=0;
    no_nodes=0;
  }
  private:
  // This function just assigns start,end and index variables to corresponding variables in segment_tree node
  void assign_iter_help(node<T> *segtree_node,int si,int ss,int se)
  {
    segtree_node[si].start=ss;
    segtree_node[si].end=se;
    segtree_node[si].index=si;
  }
  //This function checks whether the end_index falls in the limit of the inputarray size or not.
  int check_size_limit(int se)
  {
    if(input_array_size>se)
    {
      return 1;
    }
    else
    {
      return 0;
    }
  }
  void find_no_nodes(int start,int end,int count=0)
  {
    if(no_nodes<count)
    {
      no_nodes=count;
    }
    if(start==end)
    {

    }
    else
    {
      int mid=(start+end)/2;
      find_no_nodes(start,mid,2*count+1);
      find_no_nodes(mid+1,end,2*count+2);
    }
  }

public:
  /*
  This function builds segment tree if all the conditions are satisfied.
  */
  int seg_build(int ss,int se,T *inputarr,int size,auto a,int si=0,int flag=0)
  {
    /*
    Checks for 3 conditions

    1) If start_index is less than end_index or not

    2) If end_index falls within the limit of input_array_size or not

    3) If start_index is positive or not
    */
    input_array_size=size;
    if(ss>se || check_size_limit(se)==0 || ss<0)
    {
      printf("The start and end indexes are not valid\n");
      return 0;
    }
    else
    {
        find_no_nodes(ss,se);
        if(no_nodes*sizeof(node<T>)<=MAX_ARRAY_SIZE)
        {
          segtree_node=(node<T>*)malloc((no_nodes+5)*sizeof(node<T>));
          seg_main_build(ss,se,inputarr,a);
          return 1;
        }
        else
        {
          return 0;
        }
      //If all conditions are satisfied then for the actual construction of tree this method is called
    }
  }
private:
  /*
  This function is called from seg_build if all the conditions are satisfied and
  this function is responsible for segment tree construction.
  */
  T seg_main_build(int ss,int se,T *inputarr,auto a,int si=0,int flag=0)
  {
    //Checks if it is a single element or a range of multiple elements
    if(ss==se)
    {
      /*
      As this is a leaf node it just assigns the value from the input array to the segment tree node
      */
      segtree_node[si].value=inputarr[ss];
      //This step just assigns variables
      assign_iter_help(segtree_node,si,ss,se);
      return segtree_node[si].value;
    }
    int mid=(ss+se)/2;
    /*
    This is merging step where parent value is calculate from the left ,right children using the merging funtion
    */
    segtree_node[si].value=a(seg_main_build(ss,mid,inputarr,a,2*si+1,1),seg_main_build(mid+1,se,inputarr,a,2*si+2,1));
    //This step just assigns variables
    assign_iter_help(segtree_node,si,ss,se);
    return segtree_node[si].value;
  }
  // This function tells whether index lies with in the range of segment tree node or not.
  int common(int ss,int se,int index)
  {
    //Checks if it is a leaf node which corresponds to updated index or not
    if(ss==se && ss==index)
    {
      return 0;
    }
    else if(index<ss || index>se) // checks if updated index falls node<T>side the range or not
    {
      return 1;
    }
    else if(ss!=se && ss<=index && index<=se) //checks if it is non-leaf node which contains the updated index or not
    {
      return 2;
    }
  }
public:
  //This function updates the segment tree if a single change is made and if all the conditions are satisfied
  int segtree_update(int ss,int se,int index,T *inputarr,auto a,int si=0)
  {
    /*
    Checks for 3 conditions

    1) If start_index is less than end_index or not

    2) If end_index falls within the limit of input_array_size or not

    3) If start_index is positive or not
    */
    if(ss>se || check_size_limit(se)==0 || ss<0)
    {
      printf("The start and end indexes are not valid\n");
      return 0;
    }
    else
    {
      segtree_main_update(ss,se,index,inputarr,a);
      return 1;
    }
  }
  private:
  T segtree_main_update(int ss,int se,int index,T *inputarr,auto a,int si=0)
  {

    int temp=common(ss,se,index);
    if(temp==0) //Checks if it is a leaf node which corresponds to updated index or not
    {
      segtree_node[si].value=inputarr[ss];
      return segtree_node[si].value;
    }
    else if(temp==1) // checks if updated index falls node<T>side the range or not
    {
      return segtree_node[si].value;
    }
    else // //checks if it is non-leaf node which contains the updated index or not
    {
      int mid=(ss+se)/2;
      segtree_node[si].value=a(segtree_main_update(ss,mid,index,inputarr,a,2*si+1),segtree_main_update(mid+1,se,index,inputarr,a,2*si+2));
      return segtree_node[si].value;
    }
  }
public:
  int segtree_query(int ss,int se,int query_start,int query_end,T initialiser,T *inputarr,auto a,int si=0)
  {
    /*
    Checks for 3 conditions

    1) If start_index is less than end_index or not

    2) If end_index falls within the limit of input_array_size or not

    3) If start_index is positive or not
    */
    if(ss>se || check_size_limit(se)==0 || ss<0)
    {
      printf("The start and end indexes are not valid\n");
      return 0;
    }
    else
    {
      query_result=initialiser;
      segtree_main_query(ss,se,query_start,query_end,inputarr,a);
      return 1;
    }
  }
private:
  T segtree_main_query(int ss,int se,int query_start,int query_end,T *inputarr,auto a,int si=0)
  {
    if(query_start<=ss && se<=query_end)//If node range falls in query range then directly use it
    {
      query_result=a(query_result,segtree_node[si].value);
    }
    else if(ss>query_end || se<query_start)
    {
      //Do nothing if the query range and node range don't intersect
    }
    else //If node range and query range overlaps then proceed further to children.
    {
      int mid=(ss+se)/2;
      segtree_main_query(ss,mid,query_start,query_end,inputarr,a,2*si+1);
      segtree_main_query(mid+1,se,query_start,query_end,inputarr,a,2*si+2);
    }
  }

public:
  //This method returns the iterator which points to the first node i.e root of segment tree.
  node<T> *begin()
  {
    if(no_nodes>0)
    {
      node<T> *temp=&(segtree_node[0]);
      return temp;
    }
    else
    {
      //If no node is present in the tree then returns NULL
      return NULL;
    }
  }
  //This method returns the iterator which points to the parent of input iterator if any
  node<T> *get_parent(node<T> *fex)
  {
    int pos=fex->index;
    //Checks if parent exists or not and if not returns the same input iterator
    if(pos==0)
    {
      printf("This is the root of the segment tree\n");
      return fex;
    }
    else
    {
      int parent_pos=((pos-1)/2);
      fex=&(segtree_node[parent_pos]);
      //Returns parent of input iterator
      return fex;
    }
  }
  //This method returns the iterator which points to left child of input iterator if any
  node<T> * get_left_child(node<T> *fex)
  {
    int left=fex->start;
    int right=fex->end;
    //Checks if left child exists or not and if not returns the same input iterator
    if(left==right)
    {
      printf("This is a leaft node\n");
      return fex;
    }
    int pos=fex->index;
    int left_pos=2*pos+1;
    fex=&(segtree_node[left_pos]);
    //Returns left child of input iterator
    return fex;
  }
  //This method returns the iterator which points to right child of input iterator if any
  node<T> * get_right_child(node<T> *fex)
  {
    int left=fex->start;
    int right=fex->end;
    //Checks if right child exists or not and if not returns the same input iterator
    if(left==right)
    {
      printf("This is a leaf node\n");
      return fex;
    }
    int pos=fex->index;
    int right_pos=2*pos+2;
    fex=&(segtree_node[right_pos]);
    //Returns Right child of input iterator
    return fex;
  }

public:
  class Iterator
  {
  public:
    node<T> *fex;
  };
};
