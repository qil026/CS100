#ifndef BSTITERATOR_HPP
#define BSTITERATOR_HPP
#include "BSTNode.hpp"
#include <list>
#include <iterator>

/** //TODO: list real name(s) and login name(s) 
 *  // of the author(s) of this assignment
 *  
 *  Name:  Qingyang Liu
 *  Login: qil026
 *  Preferred Name: Frankie Liu
 *
 */


// declare BST here, so friend declaration below will work.
template<typename X> class BST;
template<typename X> class RST;

template<typename Data>
class BSTIterator : public std::iterator<std::input_iterator_tag,Data> {

private:

  BSTNode<Data>* curr; // pointer to this BSTIterator's current BSTNode

  /** Constructor.  Use the argument to initialize a given BSTNode
   *  in this BSTIterator.
   *  Note: this constructor is private; but friend classes can access.
   */ // TODO
  BSTIterator(BSTNode<Data>* curr) {
    if(curr == nullptr) this->curr = nullptr;
    else this->curr = curr; 
  }


public:
  // make BST a friend class, so BST can create a BSTIterator when needed.
  friend class BST<Data>;
  // make BSTNode a friend class, so BSTNode can access curr member variable.
  friend class BSTNode<Data>;
  // make RST a friend class, so RST can create a BSTIterator when needed
  friend class RST<Data>;

  /** Dereference operator.
   *  Return a copy of the Data item in the current BSTNode.
   */
  Data operator*() const {
    return curr->data;
  }
  
  /** Pre-increment operator.
   *  Update this BSTIterator to point to the inorder successor of the current
   *  BSTNode, and return a reference to the updated BSTIterator.
   */
  BSTIterator<Data>& operator++() {
    curr = curr->successor();
    return *this;
  }

  /** Post-increment operator. 
   *  Update this BSTIterator to point to the inorder successor of the current
   *  BSTNode, and return a copy of the old, non-updated BSTIterator.
   */
  BSTIterator<Data> operator++(int) {
    BSTIterator before = BSTIterator(curr);
    ++(*this);
    return before;
  }

  /** Equality test operator. */ // TODO
  bool operator==(BSTIterator<Data> const & other) const {
    // Both iterators point to valid node
    if(this->curr != nullptr && other.curr != nullptr)
      return (this->curr == other.curr);
    // Both iterators point to nullptr
    else if(this->curr == nullptr && other.curr == nullptr)
      return true;
    // One points to nullptr, the other points to valid node.
    else
      return false;
  }

  /** Inequality test operator. */ // TODO
  bool operator!=(BSTIterator<Data> const & other) const {
    //return !(this==other);
    // Both iterators point to valid node
    if(this->curr != nullptr && other.curr != nullptr)
      return (this->curr != other.curr);
    // Both iterators point to nullptr
    else if(this->curr == nullptr && other.curr == nullptr)
      return false;
    // One points to nullptr, the other points to valid node.
    else
      return true;
  }

};

#endif //BSTITERATOR_HPP
