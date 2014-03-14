#include "boggleutil.h"
#include <string>
#include <vector>
using namespace std;

// WordNode ---------------------------
WordNode::WordNode(char input, bool end){
	value = input;
	endBit = end;
	subTree = new vector<WordNode*>();
}

WordNode::~WordNode(){
	delete [] subTree;
}

WordNode*WordNode::getWordNodeFromHere(String input){
	WordNode* word = this;
	for(int i = 0; i < input.length(); i++){
		char current = input[i];
		bool found = false;
		for(int k = 0; k < word->subTree->size(); k++){
			if(current == word->subTree->get(k)->value){
				word = word->subTree-get(k);
				found = true;
				break;
			}
		}
		if(!found) return nullptr;
	}
	return word;
}

// WordTree ---------------------------
WordTree::WordTree(){
	root = new WordNode(0,false);
}

WordTree::~WordTree(){
	//delete_sub_tree(root);
	deleteSubTree(root);
	delete(root);
}

void WordTree::deleteSubTree(WordNode* node){
	int size = node->subTree->size();
	for(int i = 0; i < size; i++){
		WordNode *current = node->subTree->at(i);
		deleteSubTree(current);
	}
	delete node;
}


void WordTree::addWord(string& word){
	WordNode* node = root;
	char letter;
	bool end;
	for(int i = 0; i < word.length(); i++){
		letter = word[i];
		if(i == word.length()-1) end = true;
		else end = false; 
		bool found = false;

		int size = node->subTree->size();
		for(int i = 0; i < size; i++){
			WordNode *current = node->subTree->at(i);
			if(current->value == letter){
				found = true;
				node = current;
			}
		}

		// If no node of char value is found, create it
		if(!found){
			node->subTree->push_back(new WordNode(letter,end));
		}
		else{
			if(end) node->endBit = true;
		}
	}
}

bool WordTree::find(const string & word){
	WordNode* node = root;
	char letter;
	bool end;
	for(int i = 0; i < word.length(); i++){
		letter = word[i];
		if(i == word.length()-1) end = true;
		else end = false; 
		bool found = false;

		int size = node->subTree->size();
		for(int i = 0; i < size; i++){
			WordNode *current = node->subTree->at(i);
			if(current->value == letter){
				found = true;
				node = current;
			}
		}

		// If no node of char value is found, return false
		if(!found){
			return false;
		}
		else{
			if(end){
				if(node->endBit)
					return true;
				else
					return false;
			}
		}
	}
	return false;
}

BoardNode::BoardNode(string value){
	this->value = value;
	neighbor = new vector<BoardNode*>();
}

BoardNode::~BoardNode(){
	for(int i = 0; i < neighbor->size(); i++){
		delete neighbor->at(i);
	}
	delete neighbor;
}

// void BoardNode::setVisitedList(vector<BoardNode*> paidVisit){
// 	//add to visited list
// 	for(int i = 0; i < paidVisit.size(); i++){
// 		visited->insert(paidVisit[i]->id);
// 	}
// }


void BoardNode::setTablePosition(int rows,int cols){
	row = rows;
	col = cols;
}



void BoardNode::initializeNode(int rows, int cols, int maxCol){
	row = rows;
	col = cols;
	id = maxCol * rows + cols;
}



// BoardTree::BoardTree(){
// 	root = new BoardNode("");
// 	getNeighbors();
// }


// void BoardTree::buildBoard(BoardNode* current){
// 	// get list of neighbors
// 	getNeighbors(current);
// }


// void BoardTree::getNeighbors(BoardNode* current){
// 	int row = current->row;
// 	int col = current->col;

// 	for(int i = row-1; i <= row+1; i++){
// 		for(int k = col-1; k <= col+1; k++){
// 			// ensure i and k are within valid range
// 			if( (i>=0 && i<rows) && (k>=0 && k < cols)){
// 				// check against visited list

// 			}
// 		}
// 	}
// }



// BoardTree::initialize(unsigned int maxrows, unsigned int maxcols, string** diceArray, WordTree* dictionary){
// 	rows = maxrows;
// 	cols = maxcols;

// 	root->neighbor = new vector<BoardNode*>();

// 	// Initialize the starting point of each grid
// 	grid = new *string(rows);
// 	for(int i = 0; i < rows; i++){
// 		grid = new string(cols);
// 		for(int k = 0; k < cols; k++){
// 			grid[i][k] = diceArray[i][k];
// 			BoardNode* node = new BoardNode(diceArray[i][k]);
// 			node->initializeNode(i,k, cols);
// 			root->neighbor->push_back(node);
// 			grid
// 		}
// 	}

// 	// Now loop through each grid recursively and build tree
// 	int size = cols * rows;
// 	for(int i = 0; i < size; i++){
// 		BoardNode* current = root->neighbor->at(i);
// 		buildBoard(current);
// 	}
// }