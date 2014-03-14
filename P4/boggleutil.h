#ifndef BOGGLEUTIL_H
#define BOGGLEUTIL_H

#include <vector>
#include <string>
using namespace std;

class WordNode{
public:
	char value;
	bool endBit;
	vector<WordNode*> *subTree;

	WordNode(char, bool);
	~WordNode();

	WordNode* getWordNodeFromHere(string);
	// void recursiveDelete(WordNode*);
};


class WordTree {
public:
	WordNode* root;
	
	// void deleteSubTree(WordNode*);

	WordTree();
	~WordTree();

	void addWord(string&);
	bool find(const string&);
};


// Board Node and BoardTree
class BoardNode{
public:
	string value;
	int row, col;
	int id;

	vector<BoardNode*> *neighbor;

	BoardNode(string);
	~BoardNode();

	void initializeNode(int,int,int);
	void setVisitedList(vector<BoardNode*> paidVisit);
	void setTablePosition(int,int);
	vector<int> find(string);
};



// class BoardTree{
// public:
// 	BoardNode* root; //root will have a vector of neighbors as the starting point 
// 					 //of each grid.

// 	String** grid;

// 	unsigned int rows;
// 	unsigned int cols;

// 	void initialize(unsigned int, unsigned int, string**, WordTree*);
// 	void buildBoar(BoardNode*);
// 	void getNeighbors(BoardNode*);

// 	BoardTree();
// 	~BoardTree();
// };

#endif



