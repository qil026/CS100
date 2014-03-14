#include "boggleplayer.h"
#include "boggleutil.h"
#include <iostream>
#include <set>
#include <vector>
using namespace std;


BogglePlayer::BogglePlayer(){
	dictionary = new WordTree();
	lexiconBuilt = false;
	boardBuilt = false;
}

BogglePlayer::~BogglePlayer(){
	cout << "About to clean up boggle player" << endl;
	delete dictionary;

	// Delete board
	for(int i = 0; i < boardRows; i++){
		for(int k = 0; k < boardCols; k++){
			delete board[i][k];
		}
	}
	cout << "deleted all the board node elements" << endl;
	delete [] board;

	cout << "Cleaned up boggle player" << endl;
}


// Useless method if called before setBoard (unfortunately this is the case)
// So simply copy all the given word to the lexicon set, deal with it later
void BogglePlayer::buildLexicon(const vector<string>& word_list){
	/*  Read in each word
	 *  Use WordTree.addWord() method to add into the tree cloud
	 *  As simple as this.
	 */

	for(int i = 0; i < word_list.size(); i++){
		string word = word_list[i];
		dictionary->addWord(word);
	}

	lexiconBuilt = true;
	cout << "Lexicon is built successfully" << endl;
}


void BogglePlayer::setBoard(unsigned int rows, unsigned int cols, string** diceArray){
	/*  Construct the board in row major format
	 *  Basically same as given array
	 */

	// Initialize board 2D array of pointers
	board = new BoardNode**[rows];
	for(int i = 0; i < rows; i++){
		board[i] = new BoardNode*[cols];
		for(int k = 0; k < cols; k++){
			board[i][k] = new BoardNode(diceArray[i][k]);
			board[i][k]->initializeNode(i,k,cols);
		}
	}

	boardRows = rows;
	boardCols = cols;

	cout << "Board is initialized into 2D array of BoardNode*" << endl;

	// Construct the board trees
	// Since we have the blocks set up, loop through each and
	// build the complete tree structure.
	WordNode* word = dictionary->root;
	set<int> visited;
	for(int i = 0; i < rows; i++){
		for(int k = 0; k < cols; k++){
			BoardNode* current = board[i][k];	
			visited.insert(current->id);		
			// get neighbors only if we are not reaching the end of word tree
			WordNode* newWord = word->getWordNodeFromHere(current->value);
			if(newWord != nullptr){
				buildNeighbors(current,visited, newWord);
			}
			visited.clear();
			//cout << "Done with board[" << i << "][" << k << "]" << endl;
		}
	}



	boardBuilt = true;
	cout << "Board is built successfully" << endl;
}


bool BogglePlayer::getAllValidWords(unsigned int minimum_word_length, set<string>* words){
	/*  First check to see if lexicon and board are both built
	 *  If not, return false
	 *  Then, continue.
	 *  Given a n x n board,
	 *  create n^2 BoardTree objects
	 *  for each BoardTree, build the structure
	 *    1. create a vector of adjasent unvisited BoardNodes
	 *    2a loop through each BoardNode, stop if the string of visited nodes
	 *       no longer have corresponding valid words in dictionary
	 *    2b at each node, check the corresponding dictionary, if it has valid entry
	 *       and the number of visited nodes (including itself) is >= minimum word length
	 *       add to words set.
	 *    3. for each node, do the same in step one and two
	 *    4. When depth search in a particular node ends, return to its parent and 
	 *       continue to search its siblings.
	 *    5. The board search for this particular BoardTree is finished when all children
	 *       of root are visited.
	 */




	words->insert("lol");
	cout << "Frankie: getting all valid words" << endl;
	return true;
}

bool BogglePlayer::isInLexicon(const string& word_to_check){
	// Calls WordTree.find() method, return that result
	return dictionary->find(word_to_check);
}

vector<int> BogglePlayer::isOnBoard(const string& word_to_check){
	// Calls BoardTree.find() method, return that result
	

	vector<int> result;
	bool found = false;
	for(int i = 0; i < boardRows; i++){
		for(int k = 0; k < boardCols; k++){
			BoardNode* current = board[i][k];
			// Start your find here
			result = current->find(word_to_check);
			if(result.size() == word_to_check.length()){
				found = true;
				break;
			}
		}
		if(found) break;
	}

	if(found) return result;
	else return vector<int>;
}

void BogglePlayer::getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols){

}

void BogglePlayer::buildNeighbors(BoardNode *start, set<int> visited, WordNode* word){
	int row = start->row;
	int col = start->col;

	// Loop through its neighbors
	for(int i = row-1; i <= row+1; i++){
		for(int k = col-1; k <= col+1; k++){
			// do something to valid i,k values
			if( (i>=0 && i<boardRows) && (k>=0 && k<boardCols) ){
				BoardNode* current = board[i][k];
				int neighborId = current->id;
				set<int>::iterator result = visited.find(neighborId);
				// do something only if the node is not visited yet
				if(result == visited.end()){
					// the new neighbor is never visited.
					// Create a new BoardNode with identical information
					// Then build its subtree, and link to current 
					BoardNode *newNode = new BoardNode(current->value);
					newNode->initializeNode(i,k,boardCols);
					set<int> copy = visited;
					copy.insert(neighborId);
					// Only continue to build if dictionary is still valid
					WordNode* newWord = word->getWordNodeFromHere(current->value);
					if(newWord != nullptr){
						buildNeighbors(newNode,copy,newWord);
						// After the subtree of this new node is built
						// Link to the start node
						start->neighbor->push_back(newNode);
					}
				}
			}
		}
	}
}




