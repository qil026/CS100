#include "BST.hpp"
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

#include <stdlib.h>
#include <stdio.h>

using namespace std;


int main() {

  srand(time(0));

// Part I, insert 1000 distinct random integers into
// both vector and BST structures.
  vector<int> list;
  BST<int> tree;
  set<int> mySet;

// Test for empty() function
  if(!tree.empty())
  {
    cout << "empty() function returns incorrect value" << endl;
    return -1;
  }  

  set<int>::iterator notFound;
  pair<set<int>::iterator,bool> result;
  for(int i = 0; i < 1000; i++)
  {
    int value = rand() %10000;
    result = mySet.insert(value);
    if(result.second){
      list.push_back(value);
      tree.insert(value);
    }
    else{
      i--;
    }
  }



// Part II, compare values stored in tree and list.
// Everything found in list should also be found in tree.
// Traverse list and find corresponding value from tree.
  bool errorReport = false;
  vector<int>::iterator listIT = list.begin();
  int i;
  for(listIT = list.begin(), i = 1; listIT != list.end(); listIT++, i++){
    if(*listIT != *(tree.find(*listIT))){
      cout << "****Incorrect return value for" << *listIT << endl;
      errorReport = true;
    }
  }
  if(errorReport) return -1;
  cout << "\nPassed find() and insert() test..." << endl;

// Part III, compare sorted list with tree, values retrieved 
// from same location should be identical.
  errorReport = false;
  sort(list.begin(),list.end());
  BST<int>::iterator treeIT = tree.begin();
  for(listIT = list.begin(), i = 1; listIT != list.end(); listIT++,treeIT++,i++)
  {
    if(*listIT != *treeIT){
      cout << "****Complicting values at position: " << i << endl;
      cout << "  List: " << *listIT << "   Tree: " << *treeIT << endl;
    }
  }
  if(errorReport) return -1;
  cout << "Passed structure examination, tree is in correct order..." << endl;


// Testing size() function
  int size = tree.size();
  if(size != 1000) {
    cout << "****Size is incorrect!!!" << endl;
    return -1;
  }
  cout << "Passed size() function test..." << endl;

// Testing empty() function
  if(tree.empty()){
    cout << "****empty() function returns incorrect value!!" << endl;
    return -1;
  }
  cout << "Passed empty() function test..." << endl;

// Testing iterator inequality and equality operater
  // Test 1: two valid iterator
  BST<int>::iterator treeA = tree.begin();
  BST<int>::iterator treeB = tree.begin();
  for(int i = 0; i < 123; i++,treeA++);
  for(int i = 0; i < 567; i++,treeB++);
  if(treeA == treeB){
    cout << "****Iterator equality test failed!!!" << endl;
    return -1;
  }
  if(treeA != treeB){
    cout << "Passed equal/inequality test 1  :)" << endl;
  }
  else{
    cout << "****Iterator inequality test 1 failed!!!" << endl;
  }
  // Test 2: one valid iterator, one nullptr
  treeB = tree.end();
  if(treeA == treeB){
    cout << "****Iterator equality test failed!!!" << endl;
    return -1;
  }
  if(treeA != treeB){
    cout << "Passed equal/inequality test 2  :)" << endl;
  }
  else{
    cout << "****Iterator inequality test 2 failed!!!" << endl;
  }
  // Test 3: two nullptr
  treeA = tree.end();
  if(treeA == treeB){/* good! */}
  else{
    cout << "****Iterator equality test 3 failed!!!" << endl;
  }
  if(treeA != treeB){
    cout << "****Iterator inequality test 3 failed!!!" << endl;
  }
  else{
    cout << "Passed equal/inequality test 3  :)" << endl;
  }

// Testing clear() function
  tree.clear();
  if(tree.size() != 0) {
    cout << "****Clear() function failed to reset size to 0" << endl;
    return -1;
  }
  cout << "Passed clear() function test..." << endl;

// Testing begin iterator in an empty tree.
  treeA = tree.begin();
  treeB = tree.end();
  if(treeA != treeB){
    cout << "****begin() or end() function not implemented correctly" << endl;
    return -1;
  }
  cout << "Passed iterator implementation test..." << endl;

  cout << "\nCongradulations, you have passed all tests!!\n" << endl;

  return 0;
}
