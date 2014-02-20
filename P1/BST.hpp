#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include <utility> // for std::pair

/** //TODO: list real name(s) and login name(s) 
 *  // of the author(s) of this assignment
 *  
 *  Name:  Qingyang Liu
 *  Login: qil026
 *  Preferred Name: Frankie Liu
 *
 */


template<typename Data>
class BST {

protected:

  /** Pointer to the root of this BST, or nullptr if the BST is empty */
  BSTNode<Data>* root;

  /** Number of Data items stored in this BST. */
  unsigned int isize;


public:

  /** iterator is an aliased typename for BSTIterator<Data>. */
  typedef BSTIterator<Data> iterator;

  /** Default constructor.
      Initialize an empty BST.
   */
  BST() : root(nullptr), isize(0)  {
  }


  /** Default destructor.
   *  It is virtual, to allow appropriate destruction of subclass objects.
   *  Delete every node in this BST.
   */ // TODO
  virtual ~BST() {
    clear();
  }

  /** Insert a Data item in the BST.
   *  Return a pair, with the pair's first member set to an
   *  iterator pointing to either the newly inserted element
   *  or to the equivalent element already in the set.
   *  The pair's second element is set to true
   *  if a new element was inserted or false if an
   *  equivalent element already existed.
   */ // TODO
  virtual std::pair<iterator,bool> insert(const Data& item) {
    std::pair<iterator,bool> result (iterator(nullptr),false);
    // Special case: Empty tree. Then ititialize root item.
    if(root == nullptr){
      root = new BSTNode<Data>(item);
      root->info = -1;
      result.first = iterator(root);
      result.second = true;   
    }
    // General Case: Search tree and insert at right location
    else{
      BSTNode<Data>* current = root;
      // Search tree
      while(true){
        // Left brach, if item < current data
        if(item < current->data){
          // Recursively search into left branch
          if(current->left) current = current->left;
          // Otherwise create new node as left child
          else{
            current->left = new BSTNode<Data>(item);
            current->left->info = 0;
            current->left->parent = current;
            result.first = iterator(current->left);
            result.second = true;
            break;
          }
        }
        // Right brach, if item > current data
        else if (current->data < item){
          // Recursively search into right branch
          if(current->right) current = current->right;
          // Otherwise create new node as right child
          else{
            current->right = new BSTNode<Data>(item);
            current->right->info = 1;
            current->right->parent = current;
            result.first = iterator(current->right);
            result.second = true;
            break;
          }
        }
        // Equal branch, if item = current data
        else{
          result.first = iterator(current);
          result.second = false;
        }
      }
    }
    // Add 1 to isize for all successfull insertions.
    if(result.second) isize++;
    // Return the desired pair
    return result;
  }


  /** Find a Data item in the BST.
   *  Return an iterator pointing to the item, or the end
   *  iterator if the item is not in the BST.
   */ // TODO
  iterator find(const Data& item) const {
    BSTNode<Data>* current = root;
    while(true){
      // Left branch
      if(item < current->data){
        // Recursive step, if not found, break.
        if(current->left) {
          current = current->left;
          continue;
        }
        else break;
      }
      else if(current->data < item){
        // Recursive step, if not found, break.
        if(current->right) {
          current = current->right;
          continue;
        }
        else break;
      }
      else
        // Matching branch, since current is the matched node
        // All we need to do is break and return iterator(current).
        break;
    }
    return iterator(current);
  }

  
  /** Return the number of items currently in the BST.
   */ // TODO
  unsigned int size() const {
    return isize;
  }

  /** Remove all elements from this BST, and destroy them,
   *  leaving this BST with a size of 0.
   */ // TODO
  void clear(){
    delete_nodes(root);
    root = nullptr;
    isize = 0;
  }

  /** Return true if the BST is empty, else false.
   */ // TODO
  bool empty() const {
    return (isize == 0) ? true : false;
  }

  /** Return an iterator pointing to the first item in the BST.
   */ // TODO
  iterator begin() const {
    if(root == nullptr){
      return typename BST<Data>::iterator(nullptr);
    }
    BSTNode<Data>* current = root;
    while(current->left){
      current = current->left;
    }
    return typename BST<Data>::iterator(current);    
  }

  /** Return an iterator pointing past the last item in the BST.
   */
  iterator end() const {
    return typename BST<Data>::iterator(nullptr);
  }

private:

  void delete_nodes(BSTNode<Data>* node){
    // If node is a valid pointer
    if(node){
      if(node->left != nullptr) delete_nodes(node->left);
      if(node->right != nullptr) delete_nodes(node->right);
      delete(node);
    }
  }

 };


#endif //BST_HPP
