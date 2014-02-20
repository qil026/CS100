#ifndef RST_HPP
#define RST_HPP
#include <cstdlib>
#include <ctime>
#include "BST.hpp"
#include "BSTNode.hpp"

/** //TODO: list real name(s) and login name(s) 
 *  // of the author(s) of this assignment
 *  
 *  Name:  Qingyang Liu
 *  Login: qil026
 *  Preferred Name: Frankie Liu
 *
 */



template<typename Data>
class RST : public BST<Data>{

public:
	// Constructor
	RST()
		: BST<Data>(){
			// Allow morer andomness when creating multiple RST
			// time(0) will create the same structure for all RSTs
			int *block = (int*) malloc(sizeof(int));
			unsigned int seed = ((long int)block) % 0xffffffff;
			srand(seed);
			free(block);
		}

	~RST(){
		BST<Data>::~BST();
	}

	virtual std::pair<typename BST<Data>::iterator, bool> insert(const Data& item){
		// first generate a random number
		// then insert the node in the usual manner by calling parent method
		// add the priority tag as info
		// finally, rotate the tree to reflect its priority sequence
		
		// Create a pair to catch the result of parent insert
		// if insertion is successful, continue to attach and fix priority
		// otherwise return the same pair
		std::pair<typename BST<Data>::iterator, bool> result = BST<Data>::insert(item);
		if(result.second){
			// Create a node pointer to point to the new node
			BSTNode<Data>* node = result.first.curr;
			// Attach a random priority
			node->info = rand();
			// Fix priority sequence
			fix_priority(node);
		}	
		return result;
		
	}



//	LEVEL 2
//	Helper function
private:

	// Check to see if node has a parent and that its parent's 
	// priority is lower than that of himself
	// 	Examine whether node is a right child or a left child
	// 		Right child needs a LEFT AVL rotation
	//      Left child needs a RIGHT AVL rotation
	//	Then fix priority again if it's still not in the right position
	void fix_priority(BSTNode<Data>* node){
		if(node->parent && (node->parent->info < node->info)){
			if(node->isRightChild()){
				rotate_left(node);
			}
			else{
				rotate_right(node);
			}
			fix_priority(node);
		}
	}

	// Assumptions at function entrance:
	// node has a valid parent
	// parent has lower priority
	// node is the right child
	void rotate_left(BSTNode<Data>* node){
		BSTNode<Data>* father = node->parent;
		// Hand over left subtree
		if(node->left){
			father->right = node->left;
			father->right->parent = father;
		}
		else
			father->right = nullptr;
		
		// Fix ancestor link
		relink_ancestor(node, father);

		// Reverse biological order
		node->left = father;
		father->parent = node;
	}

	void rotate_right(BSTNode<Data>* node){
		BSTNode<Data>* father = node->parent;
		// Hand over right subtree
		if(node->right){
			father->left = node->right;
			father->left->parent = father;
		}
		else
			father->left = nullptr;

		// Fix ancestor link
		relink_ancestor(node, father);

		// Reverse biological order
		node->right = father;
		father->parent = node;		
	}

	void relink_ancestor(BSTNode<Data>* node, BSTNode<Data>* father){
		// Left father's parent (ancestor) point to node
		// so that node goes up one level
		if(father->parent){
			if(father->isRightChild()) father->parent->right = node;
			else father->parent->left = node;
			node->parent = father->parent;
		}
		else{ // father is the root
			this->root = node;	// let root point to node now
			node->parent = nullptr;
		}
	}

};


#endif
