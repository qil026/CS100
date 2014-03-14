#include "boggleutil.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// WordNode -----------------------------------------------
WordNode::WordNode(char input, bool end){
	value = input;
	endBit = end;
	subTree = new vector<WordNode*>();
}

WordNode::~WordNode(){
	int size = subTree->size();
	for(int i = 0; i < size; i++){
		WordNode* current = subTree->at(i);
		delete current;
	}
	delete subTree;
}

// void WordNode::recursiveDelete(WordNode* node){
// 	int size = node->subTree->size();
// 	for(int i = 0; i < size; i++){
// 		WordNode* current = subTree->at(i);
// 		recursiveDelete(current);
// 		delete current;
// 	}
// 	delete node->subTree;
// }


WordNode* WordNode::getWordNodeFromHere(string input){
	WordNode* word = this;
	for(int i = 0; i < input.length(); i++){
		char current = input[i];
		bool found = false;
		for(int k = 0; k < word->subTree->size(); k++){
			if(current == word->subTree->at(k)->value){
				word = word->subTree->at(k);
				found = true;
				break;
			}
		}
		if(!found) return nullptr;
	}
	return word;
}

// WordTree -----------------------------------------------
WordTree::WordTree(){
	root = new WordNode(0,false);
}

WordTree::~WordTree(){
	cout << "About to clean up word tree" << endl;
	//delete_sub_tree(root);
	delete root;
	cout << "Cleaned up word tree" << endl;
}

// void WordTree::deleteSubTree(WordNode* node){
// 	delete node;
// 	// int size = node->subTree->size();
// 	// for(int i = 0; i < size; i++){
// 	// 	WordNode *current = node->subTree->at(i);
// 	// 	deleteSubTree(current);
// 	// }
// 	// delete node;
// }


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
			WordNode* newWord = new WordNode(letter,end);
			node->subTree->push_back(newWord);
			node = newWord;
		}
		else{
			if(end) node->endBit = true;
		}
	}
}

bool WordTree::find(const string & word){
	cout << "About to find word: " << word << endl;
	WordNode* node = root;
	char letter;
	bool end;
	for(int index = 0; index < word.length(); index++){
		letter = word[index];
		cout << "  dealing with char: " << letter << endl;
		if(index == word.length()-1) end = true;
		else end = false; 
		bool found = false;

		int size = node->subTree->size();
		for(int i = 0; i < size; i++){
			cout << "     Looping through subTree, i=" << i;
			WordNode *current = node->subTree->at(i);
			cout << "  char=" << current->value << endl;
			if(current->value == letter){
				cout << "    Found a match!!!" << endl;
				found = true;
				node = current;
				break;
			}
		}

		// If no node of char value is found, return false
		if(!found){
			cout << "  didn't find subsequent letters. stop" << endl;
			return false;
		}
		else{
			cout << " found subsequent letters, continue" << endl;
			if(end){
				if(node->endBit)
					return true;
				else
					return false;
			}
		}
	}
	cout << "Finished finding word" << endl;
	return false;
}





// BoardNode ----------------------------------------------
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

vector<int> BoardNode::find(string input){
	if(input.length() == 0) return vector<int>;
	if(input.length() < value.length()) return vector<int>;
	// this node contains value
	string currentValue = value;
	bool match = true;

	int i = 0;
	for(i; i < currentValue.length(); i++){
		if(currentValue[i] != input[i]) match = false;
	}
	if (!match) return vector<int>;
	// otherwise
	// get sub string
	string output = "";
	for(i; i < input.length(); i++) output += input[i];
	for(int index = 0; index < neighbor->size(); index++){
		BoardNode* next = neighbor->at(index);
		vector<int> nextResult = find(output);
		if(nextResult.size()==output.length()){
			nextResult.push_back(id);
			return nextResult;
		}
	}
	return vector<int>;	
}


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