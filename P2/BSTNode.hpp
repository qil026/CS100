#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include <iostream>
#include <iomanip>

/** //TODO: list real name(s) and login name(s) 
 *  // of the author(s) of this assignment
 *  
 *  Name:  Qingyang Liu
 *  Login: qil026
 *  Preferred Name: Frankie Liu
 *
 */


/** This class template defines a node type for the BST container.
 *  Note that all members are public. So, the BST implementation should
 *  take care not to expose any BSTNode objects.
 */
template<typename Data>
class BSTNode {

public:

  /** Member variables. */
  BSTNode<Data>* parent;
  BSTNode<Data>* left;
  BSTNode<Data>* right;
  const Data data;  // the const Data in this node
  int info;  // variable used in advanced algorithms 

  /** Constructor.  Initialize a BSTNode with the given Data item,
   *  no parent, and no children.
   */
  BSTNode(const Data & d): data(d) {
    left = right = parent = nullptr;
  }


  /** Return the inorder successor of this BSTNode in a BST,
   *  or nullptr if none.
   *  PRECONDITION: this BSTNode is a node in a BST.
   *  POSTCONDITION:  the BST is unchanged.
   *  RETURNS: the BSTNode that is the inorder successor of this BSTNode,
   *  or nullptr if there is none.
   */ // TODO
  BSTNode<Data>* successor() const {
    BSTNode<Data>* result;
    // Case 1: No right child
    if(right == nullptr){
      // Algorithm simplification step
      result = parent;
      // If parent is a right child keep searching up
      // Otherwise, the parent is the successor already.
      if(this->isRightChild()){
        while(result->isRightChild()){
          if(result->parent) result = result->parent;
          else return nullptr;
        }
        result = result->parent;
      }
    }
    // Case 2: Has right child
    else{
      // Search for the smallest(left child) in the right subtree
      result = right;
      while(result->left) result = result->left;
    }
    return result;
  }
  
//  returns true if the node is a right child
//  returns false if the node is a left child or root
  bool isRightChild() const{
    if(this->parent){
      if(this->parent->right == this)
      return true;
      else return false;
    }
    else
      return false;
  }
  
}; 

/** Overload operator<< to insert a BSTNode's fields in an ostream. */
template <typename Data>
std::ostream & operator<<(std::ostream& stm, const BSTNode<Data> & n) {
  stm << '[';
  stm << std::setw(10) << &n;                 // address of the BSTNode
  stm << "; p:" << std::setw(10) << n.parent; // address of its parent
  stm << "; l:" << std::setw(10) << n.left;   // address of its left child
  stm << "; r:" << std::setw(10) << n.right;  // address of its right child
  stm << "; i:" << std::setw(10) << n.info;   // its info field
  stm << "; d:" << n.data;                    // its data field
  stm << ']';
  return stm;
}

#endif // BSTNODE_HPP
